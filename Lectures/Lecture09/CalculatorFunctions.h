// header guards (#ifndef, #define, #endif) guard against the same file being
// included multiple times through a divergent dependency chain.  if a header
// were to be included twice, it would result in compiler redeclaration
// errors
#ifndef CALCULATOR_FUNCTIONS_H
#define CALCULATOR_FUNCTIONS_H

// first need to declare our functions
// forward declaration, use the function prototype
// place comment block on function prototype

/**
 * @brief sums two doubles
 * @param LHS left hand side value to add
 * @param RHS right hand side value to add
 * @return double sum of left and right hand sides
 */
double add(double LHS, double RHS);

/**
 * @brief subtracts two doubles
 * @param LHS left hand side value to subtract
 * @param RHS right hand side value to subtract
 * @return double difference of left and right hand sides
 */
double sub(double LHS, double RHS);

/**
 * @brief multiplies two doubles
 * @param LHS left hand side value to multiply
 * @param RHS right hand side value to multiply
 * @return double product of left and right hand sides
 */
double mult(double LHS, double RHS);

/**
 * @brief divides two doubles
 * @param LHS numerator
 * @param RHS denominator
 * @return double quotient of numerator divided by denominator
 */
double div(double LHS, double RHS);

/**
 * @brief implements floating point modulus operator
 * @param LHS numerator 
 * @param RHS denominator
 * @return double remainder leftover of numerator / denominator
 */
double mod(double LHS, double RHS);

/**
 * @brief prints to standard out the template: "LHS op RHS = result" ending with a newline
 * @param LHS left hand side value
 * @param OP operator
 * @param RHS right hand side value
 * @param RESULT resultant value
 */
void print_equation(double LHS, char OP, double RHS, double RESULT);

#endif