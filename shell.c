#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void showme(const char *filename, FILE *outfile) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(outfile, "File not found: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        fprintf(outfile, "%s", line);
    }

    fclose(file);
}

void junk(const char *filename, FILE *outfile) {
    if (remove(filename) != 0) {
        fprintf(outfile, "File not found, failed to junk %s\n", filename);
    } else {
        fprintf(outfile, "File successfully removed: %s\n", filename); 
    }
}

void createf(const char *filename, FILE *outfile) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(outfile, "Failed to create file: %s\n", filename);
        return;
    }
    fclose(file);
    fprintf(outfile,"Created file %s\n",filename);
}

void lstdir(FILE *outfile) {
    FILE *fp = popen("ls", "r");
    if (fp == NULL) {
        fprintf(outfile, "Failed to list the directory contents\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        fprintf(outfile, "%s", line);
    }

    pclose(fp);
}

void parse_log(const char *input_file, const char *output_file, FILE *outfile) {
    char command[MAX_LINE_LENGTH];
    snprintf(command, sizeof(command), "./parse_log %s %s", input_file, output_file);

    if (system(command) == 0) {
        fprintf(outfile, "parse_log completed for input file %s, output file %s\n", input_file, output_file);
    } else {
        fprintf(outfile, "Error executing log parser command\n");
    }
}

void execute_command(const char *command, FILE *outfile) {
    char cmd[MAX_LINE_LENGTH];
    sscanf(command, "%s", cmd);

    if (strcmp(cmd, "showme") == 0) {
        char filename[MAX_LINE_LENGTH];
        sscanf(command, "%*s %s", filename);
        showme(filename, outfile);
    } else if (strcmp(cmd, "junk") == 0) {
        char filename[MAX_LINE_LENGTH];
        sscanf(command, "%*s %s", filename);
        junk(filename, outfile);
    } else if (strcmp(cmd, "createf") == 0) {
        char filename[MAX_LINE_LENGTH];
        sscanf(command, "%*s %s", filename);
        createf(filename, outfile);
    } else if (strcmp(cmd, "lstdir") == 0) {
        lstdir(outfile);
    } else if (strcmp(cmd, "parse_log") == 0) {
        char input_filename[MAX_LINE_LENGTH];
        char output_filename[MAX_LINE_LENGTH];
        sscanf(command, "%*s %s %s", input_filename, output_filename);
        parse_log(input_filename, output_filename, outfile);
    } else {
        fprintf(outfile, "Unknown command: %s\n", command); 
    }
}

void process_commands(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "r");
    if (infile == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE *outfile = fopen(output_file, "w");
    if (outfile == NULL) {
        perror("Error opening output file");
        fclose(infile);
        return;
    }

    char command[MAX_LINE_LENGTH];
    while (fgets(command, sizeof(command), infile)) {
        command[strcspn(command, "\n")] = 0; 
        execute_command(command, outfile);
    }

    fclose(infile);
    fclose(outfile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <inputfile.txt> <outputfile.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    process_commands(input_filename, output_filename);
    return EXIT_SUCCESS;
}
