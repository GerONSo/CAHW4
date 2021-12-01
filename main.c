#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern double square(__uint8_t, double, double, double);

const int MAX_SIZE = 10000;

struct Figure {
    __uint8_t figureFlag;
    int main;
    int first;
    int second;
    int third;
};

int readFile(FILE* file, struct Figure* figures) {
    int current = 0;
    while (!feof(file) && current < MAX_SIZE) {
        char result[20];
        fscanf(file, "%s", result);
        if (strcmp(result, "Sphere") == 0) {
            figures[current].figureFlag = 1;
            fscanf(file, "%d %d", &figures[current].main, &figures[current].first);
        } else if (strcmp(result, "Parallelepiped") == 0) {
            figures[current].figureFlag = 2;
            fscanf(file, "%d %d %d %d", &figures[current].main, &figures[current].first, &figures[current].second, &figures[current].third);
        } else if (strcmp(result, "Tetrahedron") == 0) {
            figures[current].figureFlag = 3;
            fscanf(file, "%d %d", &figures[current].main, &figures[current].first);
        } else {
            printf("Incorrect figure name");
            exit(1);
        }
        ++current;
    }
    return current;
}

void printFile(FILE* file, struct Figure* figures, int size) {
    for (int i = 0; i < size; i++) {
        if (figures[i].figureFlag == 1) {
            fprintf(file, "Sphere {\n\tdensity: %d,\n\tradius: %d,\n\tsquare(): %f\n}\n", 
                    figures[i].main, 
                    figures[i].first, 
                    square(
                        figures[i].figureFlag, 
                        figures[i].first,
                        figures[i].second,
                        figures[i].third
                    ));
        } else if (figures[i].figureFlag == 2) {
            fprintf(file, "Parallelepiped {\n\tdensity: %d\n\tlength: %d,\n\twidth: %d,\n\theight: %d,\n\tsquare(): %f\n}\n",
                    figures[i].main,
                    figures[i].first,
                    figures[i].second,
                    figures[i].third,
                    square(
                        figures[i].figureFlag, 
                        figures[i].first,
                        figures[i].second,
                        figures[i].third
                    ));
        } else if (figures[i].figureFlag == 3) {
            fprintf(file, "Tetrahedron {\n\tdensity: %d,\n\tedgeLength: %d,\n\tsquare(): %f\n}\n",
                    figures[i].main,
                    figures[i].first,
                    square(
                        figures[i].figureFlag, 
                        figures[i].first,
                        figures[i].second,
                        figures[i].third
                    ));
        }
    }
}

void sort(struct Figure* figures, int size) {
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && square(
                        figures[j].figureFlag, 
                        figures[j].first,
                        figures[j].second,
                        figures[j].third
                    ) < square(
                        figures[j - 1].figureFlag, 
                        figures[j - 1].first,
                        figures[j - 1].second,
                        figures[j - 1].third
                    )) {
            struct Figure figure = figures[j];
            figures[j] = figures[j - 1];
            figures[j - 1] = figure;
            j--;
        }
    }
}

struct Figure getRandomFigure() {
    int figureNumber = rand() % 3;
    int MAX_LENGTH = 1000;
    struct Figure figure;
    if (figureNumber == 0) {
        int radius = rand() % MAX_LENGTH;
        figure.figureFlag = 1;
        figure.first = radius;
    } else if (figureNumber == 1) {
        int length = rand() % MAX_LENGTH;
        int width = rand() % MAX_LENGTH;
        int height = rand() % MAX_LENGTH;
        figure.figureFlag = 2;
        figure.first = length;
        figure.second = width;
        figure.third = height;
    } else {
        int edgeLength = rand() % MAX_LENGTH;
        figure.figureFlag = 3;
        figure.first = edgeLength;
    }
    return figure;
}


void runWithDefaultInput(char* argv[]) {
    char* inputFilePath = argv[2];
    char* outputFilePath = argv[3];
    char* outputSortedFilePath = argv[4];
    FILE* file = fopen(inputFilePath, "r");
    FILE* outputFile = fopen(outputFilePath, "w+");
    FILE* outputSortedFile = fopen(outputSortedFilePath, "w+");
    if (file == NULL) {
        perror(inputFilePath);
    } else if (outputFile == NULL) {
        perror(outputFilePath);
    } else if (outputSortedFile == NULL) {
        perror(outputSortedFilePath);
    } else {
        struct Figure figures[MAX_SIZE]; 
        int size = readFile(file, figures);
        printFile(outputFile, figures, size);
        sort(figures, size);
        printFile(outputSortedFile, figures, size);
    }
    fclose(file);
    fclose(outputFile);
    fclose(outputSortedFile);
}

void runWithRandomInput(char* argv[]) {
    int figuresNumber = atoi(argv[2]);
    char* outputFilePath = argv[3];
    char* outputSortedFilePath = argv[4];
    FILE* outputFile = fopen(outputFilePath, "w+");
    FILE* outputSortedFile = fopen(outputSortedFilePath, "w+");
    if (figuresNumber > MAX_SIZE || figuresNumber < 0) {
        printf("Number of elements is incorrect:\nNumber should be in [%d;%d]\n", 1, MAX_SIZE);
        exit(1);
    }
    struct Figure figures[MAX_SIZE]; 
    for (int i = 0; i < figuresNumber; i++) {
        figures[i] = getRandomFigure();
    }
    printFile(outputFile, figures, figuresNumber);
    sort(figures, figuresNumber);
    printFile(outputSortedFile, figures, figuresNumber);
    fclose(outputFile);
    fclose(outputSortedFile);
}

void onIncorrectArgumentCount(char* argv[]) {
    printf("Amount of arguments is incorrect:\n");
    printf("Try %s -f .../input.txt .../output.txt .../output_sorted.txt\n", argv[0]);
    printf("OR\n%s -r items_count\n", argv[0]);
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        onIncorrectArgumentCount(argv);
    }
    char* flag = argv[1];
    if (argc == 5 && strcmp(flag, "-f") == 0) {
        runWithDefaultInput(argv);
    } else if (argc == 5 && strcmp(flag, "-r") == 0) {
        runWithRandomInput(argv);
    } else {
        onIncorrectArgumentCount(argv);
    }
    return 0;
}