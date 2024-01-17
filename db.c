#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
} Statement;

void close_input_buffer(char* input) { free(input); }

void remove_newline(char* input) { input[strcspn(input, "\n")] = '\0'; }

MetaCommandResult do_meta_command(char* input) {
  if (strcmp(input, ".exit") == 0) {
    close_input_buffer(input);
    exit(0);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

PrepareResult prepare_statement(char* input, Statement* statement) {
  if (strncmp(input, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }
  if (strncmp(input, "select", 6) == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
  switch (statement->type) {
    case (STATEMENT_INSERT):
      printf("This is where we would do an insert.\n");
      break;
    case (STATEMENT_SELECT):
      printf("This is where we would do a select.\n");
      break;
  }
}

int main() {
  char input[100];
  while (1) {
    printf("Enter command: ");
    fgets(input, 100, stdin);
    remove_newline(input);

    if (input[0] == '.') {
      switch (do_meta_command(input)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNIZED_COMMAND):
          printf("Unrecognized command '%s'\n", input);
          continue;
      }
    }
    Statement statement;
    switch (prepare_statement(input, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s'.\n", input);
        continue;
    }

    execute_statement(&statement);
    printf("Executed.\n");
  }

  return 0;
}