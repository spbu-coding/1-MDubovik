#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 100
#define PARTITION_SIZES_LENGTH 6
double calculate_rectangle_rule(double left_border, double right_border) {
    return (right_border - left_border) * sin((left_border + right_border) / 2);
}

double calculate_simpsons_rule(double left_border, double right_border) {
    return (right_border - left_border) / 6 * (sin(left_border) + 4 * sin((left_border + right_border) / 2) + sin(right_border));
}

char **calculate_area(double a, double b, int partition_sizes[], int count) {
    char **outputs = malloc(sizeof(char *) * count);
    for (int i = 0; i < count; i++) {
        double area_by_rectangle = 0.0, area_by_simpsons = 0.0;
        double part_length = (b - a) / partition_sizes[i];
        double left_border = a, right_border = a + part_length;
        for (int j = 0; j < partition_sizes[i]; j++) {
            area_by_rectangle += calculate_rectangle_rule(left_border, right_border);
            area_by_simpsons += calculate_simpsons_rule(left_border, right_border);
            left_border += part_length;
            right_border += part_length;
        }

        char *output = malloc(sizeof(char) * MAX_STRING_SIZE);
        sprintf(output, "%d %.5lf %.5lf", partition_sizes[i], area_by_rectangle, area_by_simpsons);
        outputs[i] = output;
    }
    return outputs;
}

void free_outputs(char **outputs, int count)
{
    for (int i = 0; i < count; ++i)
    {
        free(outputs[i]);
    }
    free(outputs);
}

int main()
{
    int partition_sizes[] = {6, 10, 20, 100, 500, 1000};
    printf("Enter the left and right borders: ");
    double a, b;
    scanf("%lf %lf", &a, &b);
    char **outputs = calculate_area(a, b, partition_sizes, PARTITION_SIZES_LENGTH);
    for (int i = 0; i < PARTITION_SIZES_LENGTH; i++)
    {
        printf("%s\n", outputs[i]);
    }

    free_outputs(outputs, PARTITION_SIZES_LENGTH);

    return 0;
}
