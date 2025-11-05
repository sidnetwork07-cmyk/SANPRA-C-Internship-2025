#include <stdio.h>

int main() {
    int choice;
    double num1, num2, result;

    printf("Welcome to the Mini Calculator!\n");

    while (1) {
        printf("\nSelect operation:\n");
        printf("1. Add\n");
        printf("2. Subtract\n");
        printf("3. Multiply\n");
        printf("4. Divide\n");
        printf("5. Exit\n");
        printf("Enter choice (1-5): ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Thank you for using the calculator. Goodbye!\n");
            break;
        }

        if (choice >= 1 && choice <= 4) {
            printf("Enter first number: ");
            scanf("%lf", &num1);
            printf("Enter second number: ");
            scanf("%lf", &num2);

            switch (choice) {
                case 1:
                    result = num1 + num2;
                    printf("%.2f + %.2f = %.2f\n", num1, num2, result);
                    break;
                case 2:
                    result = num1 - num2;
                    printf("%.2f - %.2f = %.2f\n", num1, num2, result);
                    break;
                case 3:
                    result = num1 * num2;
                    printf("%.2f * %.2f = %.2f\n", num1, num2, result);
                    break;
                case 4:
                    if (num2 == 0) {
                        printf("Error! Division by zero.\n");
                    } else {
                        result = num1 / num2;
                        printf("%.2f / %.2f = %.2f\n", num1, num2, result);
                    }
                    break;
            }
        } else {
            printf("Invalid choice! Please select a valid operation.\n");
        }
    }

    return 0;
}
