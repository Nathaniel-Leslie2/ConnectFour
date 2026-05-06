#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 6
#define COLS 7
#define EMPTY '.'
#define PLAYER_ONE 'X'
#define PLAYER_TWO 'O'

static void initialize_board(char board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col] = EMPTY;
        }
    }
}

static void print_board(char board[ROWS][COLS]) {
    printf("\n");
    for (int row = 0; row < ROWS; row++) {
        printf("| ");
        for (int col = 0; col < COLS; col++) {
            printf("%c ", board[row][col]);
        }
        printf("|\n");
    }

    printf("  ");
    for (int col = 1; col <= COLS; col++) {
        printf("%d ", col);
    }
    printf("\n\n");
}

static bool is_valid_column(char board[ROWS][COLS], int column) {
    return column >= 0 && column < COLS && board[0][column] == EMPTY;
}

static int drop_piece(char board[ROWS][COLS], int column, char piece) {
    for (int row = ROWS - 1; row >= 0; row--) {
        if (board[row][column] == EMPTY) {
            board[row][column] = piece;
            return row;
        }
    }

    return -1;
}

static bool board_full(char board[ROWS][COLS]) {
    for (int col = 0; col < COLS; col++) {
        if (board[0][col] == EMPTY) {
            return false;
        }
    }

    return true;
}

static bool within_bounds(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

static bool check_direction(char board[ROWS][COLS], int start_row, int start_col,
                            int row_step, int col_step, char piece) {
    for (int i = 0; i < 4; i++) {
        int row = start_row + (i * row_step);
        int col = start_col + (i * col_step);
        if (!within_bounds(row, col) || board[row][col] != piece) {
            return false;
        }
    }

    return true;
}

static bool is_winning_move(char board[ROWS][COLS], int row, int col, char piece) {
    const int directions[4][2] = {
        {0, 1},   // Horizontal
        {1, 0},   // Vertical
        {1, 1},   // Diagonal down-right
        {1, -1}   // Diagonal down-left
    };

    for (int direction = 0; direction < 4; direction++) {
        int row_step = directions[direction][0];
        int col_step = directions[direction][1];

        for (int offset = -3; offset <= 0; offset++) {
            int start_row = row + (offset * row_step);
            int start_col = col + (offset * col_step);
            if (check_direction(board, start_row, start_col, row_step, col_step, piece)) {
                return true;
            }
        }
    }

    return false;
}

static bool parse_column_input(const char *input, int *column) {
    if (input == NULL) {
        return false;
    }

    while (isspace((unsigned char)*input)) {
        input++;
    }

    if (*input == '\0') {
        return false;
    }

    if (*input == 'q' || *input == 'Q') {
        return false;
    }

    char *endptr = NULL;
    long value = strtol(input, &endptr, 10);
    if (endptr == input) {
        return false;
    }

    while (isspace((unsigned char)*endptr)) {
        endptr++;
    }

    if (*endptr != '\0') {
        return false;
    }

    if (value < 1 || value > COLS) {
        return false;
    }

    *column = (int)value - 1;
    return true;
}

int main(void) {
    char board[ROWS][COLS];
    char current_player = PLAYER_ONE;
    char input_buffer[64];

    initialize_board(board);

    printf("Connect Four (Terminal Edition)\n");
    printf("Players take turns dropping pieces into columns 1-%d.\n", COLS);
    printf("Type q to quit.\n");

    while (true) {
        print_board(board);
        printf("Player %c, choose a column (1-%d) or q to quit: ", current_player, COLS);

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
            printf("\nInput stream closed. Ending game.\n");
            break;
        }

        if (input_buffer[0] == 'q' || input_buffer[0] == 'Q') {
            printf("Game ended by player request.\n");
            break;
        }

        int column = -1;
        if (!parse_column_input(input_buffer, &column)) {
            printf("Invalid input. Please enter a number from 1 to %d.\n", COLS);
            continue;
        }

        if (!is_valid_column(board, column)) {
            printf("Column %d is full or out of range. Choose a different column.\n", column + 1);
            continue;
        }

        int placed_row = drop_piece(board, column, current_player);
        if (placed_row == -1) {
            printf("Unable to place piece in column %d. Try again.\n", column + 1);
            continue;
        }

        if (is_winning_move(board, placed_row, column, current_player)) {
            print_board(board);
            printf("Player %c wins!\n", current_player);
            break;
        }

        if (board_full(board)) {
            print_board(board);
            printf("It's a draw!\n");
            break;
        }

        current_player = (current_player == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
    }

    return 0;
}
