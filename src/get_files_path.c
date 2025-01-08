#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/get_files_path.h"

#ifdef __unix__
    #include <errno.h>
    #include <sys/stat.h>  // For mkdir and stat functions
#endif

#ifdef WIN64
    #include <windows.h>
    #include <shlobj.h>
#endif

#ifdef __unix__

char* output = NULL;
int does_file_exist(const char * filepath){
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
}


char* return_folders_path() {
    char command[] = "echo $HOME";
    char buffer[128];
    char directory[] = "/MCWordle";

    // Open a pipe to execute the command
    FILE *pipe = popen(command, "r");
    if (pipe == NULL) {
        perror("Running Command Failed");
        return NULL;
    }

    // Read the output of the command into buffer
    if (fgets(buffer, sizeof(buffer), pipe) == NULL) {
        perror("Failed to read command output");
        pclose(pipe);
        return NULL;
    }
    pclose(pipe);

    // Remove newline character from buffer
    for (int i = 0; i < sizeof(buffer) / sizeof(char); i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break; // No need to continue checking after null terminator
        }
    }

    // Allocate memory for the full path
    size_t path_length = strlen(buffer) + strlen(directory) + 1; // +1 for null terminator
    output = malloc(path_length);
    if (output == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    // Construct the full path
    strcpy(output, buffer);
    strcat(output, directory);
    fprintf(stdout, "return_folders_path: %s\n", output);

    // Check if the path exists
    if (!does_file_exist(output)) {
        errno = ENOENT; // Set error code for "No such file or directory"
        fprintf(stderr, "Path: %s: ", output);
        perror("");
        fprintf(stderr, "\n");
        free(output); // Free allocated memory if the path does not exist
        output = NULL;
    }

    return output;
}

#endif

#ifdef WIN64

char* output;

char* return_folders_path() {
    // GUID for the Documents folder
    PWSTR path = NULL;
    HRESULT result = SHGetKnownFolderPath(&FOLDERID_Documents, 0, NULL, &path);

    if (result != S_OK) {
        fprintf(stderr, "Error retrieving the Documents path.\n");
        return NULL;
    }

    // Convert the wide character string to a regular char string
    size_t size = wcslen(path) + 1;
    char *buffer = (char *)malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        CoTaskMemFree(path);
        return NULL;
    }
    wcstombs(buffer, path, size);

    // Directory to append
    char directory[] = "/myGames/Jtetris/";

    // Allocate memory for the combined path
    output = (char *)malloc(strlen(buffer) + strlen(directory) + 1);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(buffer);
        CoTaskMemFree(path);
        return NULL;
    }

    // Create the final path
    strcpy(output, buffer);
    strcat(output, directory);

    // Print the result for debugging
    fprintf(stdout, "return_folders_path: %s\n", output);

    // Free allocated memory for `path` and `buffer`
    free(buffer);
    CoTaskMemFree(path);

    return output;
}

void free_folders_ptr(){
    free(output);
}

int does_file_exist(const char * filepath){
// Windows-specific method
    DWORD attributes = GetFileAttributesA(filepath);
    return (attributes != INVALID_FILE_ATTRIBUTES && 
            !(attributes & FILE_ATTRIBUTE_DIRECTORY));
}
#endif
