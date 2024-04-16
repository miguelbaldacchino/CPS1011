#include <stdio.h>
#include <stdlib.h>
#include<math.h>

void clearBuffer();
double *getCoefficients();
void displayPolynomial();
double polynomial(double x);
double derivative(double x);
double newtonRaphson();

double *coeff; // Global variable to tore coefficients

void clearBuffer() { // clears buffer
    while (getchar() != '\n');
}

void displayPolynomial() { // Displays entered polynomial
    printf("Your polynomial is:\n %.3fx^5 + %.3fx^4 + %.3fx^3 + %.3fx^2 + %.3fx + %.3f\n",
           coeff[5], coeff[4], coeff[3], coeff[2], coeff[1], coeff[0]);
}

void displayDerivative() { // Displays entered derivative of polynomial0
    printf("\nThe derivative is:\n %.3fx^4 + %.3fx^3 + %.3fx^2 + %.3fx + %.3f\n",
           5 * coeff[5], 4 * coeff[4], 3 * coeff[3], 2 * coeff[2], coeff[1]);
}

double *getCoefficients() { // gets coefficients from user
    coeff = (double *) malloc(6 * sizeof(double)); // Memory allocated for coefficients

    if (coeff == NULL) { // checks successful memory allocation
        printf("Error: Memory allocation has failed\n");
        return NULL; // indicates memory allocation failure
    }

    while (1) {
        printf("\nAx^5 + Bx^4 + Cx^3 + Dx^2 + Ex + F\n");
        printf("Enter coefficients of polynomial (A B C D E F)\n");

        if (scanf("%lf %lf %lf %lf %lf %lf",
                  &coeff[5], &coeff[4], &coeff[3], &coeff[2], &coeff[1], &coeff[0]) == 6) {

            if (coeff[0] == 0 && coeff[1] == 0 && coeff[2] == 0 && coeff[3] == 0 && coeff[4] == 0 && coeff[5] == 0) {
                printf("All coefficients are zero. Root is trivially 0.\n");
                free(coeff);
                return NULL;
            }

            displayPolynomial();

            break;

        } else {
            printf("Error: Invalid input. Please provide coefficients in the correct format.");
            clearBuffer();
        }
    }

    return coeff;
}

double polynomial(double x) { // Creates polynomial
    return (coeff[5] * pow(x, 5)) + (coeff[4] * pow(x, 4)) + (coeff[3] * pow(x, 3)) + (coeff[2] * pow(x, 2)) +
            (coeff[1] * x) + (coeff[0]);

}

double derivative(double x) { // Creates derivative of polynomial
    return (5 * coeff[5] * pow(x, 4)) + (4 * coeff[4] * pow(x, 3)) + (3 * coeff[3] * pow(x, 2)) + (2 * coeff[2] * x) +
            (coeff[1]);

}

double getInitialGuess(int order) {
    double guess;

    printf("\nEnter the initial guess for x%d:\n", order);
    while (scanf("%lf", &guess) != 1) {
        clearBuffer();
        printf("Error: Invalid input. Please enter a valid numerical value.\n");
        printf("Enter the initial guess for x%d:\n", order);
    }
    clearBuffer();

    return guess;
}

double getTolerance() {
    double tolerance;

    printf("\nEnter the tolerable error for convergence (e.g., 0.00001):\n");
    while (scanf("%lf", &tolerance) != 1 || tolerance <= 0) {
        clearBuffer();
        printf("Error: Invalid input. Please enter a valid positive numerical value.\n");
        printf("Enter the tolerable error for convergence:\n");
    }
    clearBuffer();

    return tolerance;
}

int getMaxIterations() {
    int maxItr;

    printf("\nEnter the maximum number of iterations:\n");
    while (scanf("%d", &maxItr) != 1 || maxItr <= 0) {
        clearBuffer();
        printf("Error: Invalid input. Please enter a valid positive integer value.\n");
        printf("Enter the maximum number of iterations:\n");
    }
    clearBuffer();

    return maxItr;
}

double newtonRaphson() { // Newton-Raphson method
    clearBuffer();
    printf("Newton-Raphson Method\n");
    printf("_____________________\n");
    double x0, x1, tolerance; // x0 -> Initial Guess | x1 -> Calculated Root
    int i = 1, maxItr;

    coeff = getCoefficients(); // Get coefficients from user

    if (coeff == NULL) {
        printf("Error: Coefficients allocation failed\n");
        return 0;
    }

    clearBuffer();

    displayDerivative();

    x0 = getInitialGuess(0);
    tolerance = getTolerance();
    maxItr = getMaxIterations();

    if (maxItr < 1) {
        printf("\nError: Iterations must be larger than 0\n");
        return 0;
    }

    do {
        if (derivative(x0) == 0) {
            printf("Error: Mathematical Error, Denominator equal to zero");
            break;
        }



        x1 = x0 - (polynomial(x0) / derivative(x0));
        printf("At iteration %d: x = %f\n", i, x1);
        // Check if the absolute difference is less than the tolerance
        if (fabs(polynomial(x1)) < tolerance) {
            printf("\nConverged to the desired tolerance.\n");
            break;
        }
        x0 = x1;
        i++;
    } while (i <= maxItr);

    if (i <= maxItr && derivative(x0) != 0) {
        printf("\nRoot found successfully.\n");
    } else {
        printf("\nRoot not found within the specified tolerance or maximum iterations.\n");
    }
    free(coeff);
    return x1;
}

double secantMethod () { // Secant Method
    clearBuffer();
    printf("Secant Method\n");
    printf("_____________________\n");
    double x0, x1, x2, tolerance; // x0, x1 -> initial guesses x2 -> root approximation
    int i = 1, maxItr;

    coeff = getCoefficients(); // Get coefficients from user

    if (coeff == NULL) {
        printf("Error: Coefficients allocation failed\n");
        return 0;
    }

    clearBuffer();

    x0 = getInitialGuess(0);
    x1 = getInitialGuess(1);

    tolerance = getTolerance();
    maxItr = getMaxIterations();

    if (maxItr < 1) {
        printf("Error: Iterations must be larger than 0\n");
        return 0;
    }

    do {
        if (polynomial(x1) - polynomial(x0) == 0) {
            printf("Error: Mathematical Error, Denominator equal to zero");
            break;
        }

        // Check if the absolute difference is less than the tolerance
        if (fabs(polynomial(x2)) < tolerance) {
            printf("\nConverged to the desired tolerance.\n");
            break;
        }

        x2 = x1 - (polynomial(x1) * ( (x1 - x0) / (polynomial(x1) - polynomial(x0)) ) );
        printf("At iteration %d: x = %f\n", i, x2);

        x0 = x1;
        x1 = x2;  // Update x0 and x1 after checking convergence

        i++;
    } while (i <= maxItr && polynomial(x1) - polynomial(x0) != 0);

    return x2;
}

void showMenu() {
    printf("\nRoot-Finding Methods Menu\n");
    printf("1. Newton-Raphson Method\n");
    printf("2. Secant Method\n");
    printf("3. Exit\n");
    printf("Enter your choice (1, 2, or 3):\n");
}

int main() {
    int choice;

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();  // Clear the input buffer
            continue;  // Skip the rest of the loop and ask for input again
        }
        switch (choice) {
            case 1 : newtonRaphson(); break;
            case 2 : secantMethod(); break;
            case 3 :
                printf("Exiting");
                return 0;
            default:
                printf("Wrong input\n");
                break;
        }
    }
}