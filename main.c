//
//  main.c
//  CalculatorProject
//
//  Created by Anus Moore on 11/12/2018.
//  Copyright © 2018 Leeds.ac.uk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

//Arbitary values for left and right associativity
#define LEFT_ASSOCIATIVE 4
#define RIGHT_ASSOCIATIVE 5

int MAXSIZE = 100; //Max size an array can be, 100 is plenty of space.

char InputString[16]; //Input infix expression string array, 16 max due to LCD screen width
char operatorStack[16]; //Operator stack array
char RPNQue[50]; //Output reverse polish notation array, is longer due to added spacing in the string
char doubleConversionStack[16]; //Stack for converting RPN character strings into double values.
double evaluationStack[16]; //RPM evaluation array


//End of array indicators
int topOperator = -1;
int endOfRPNOutputQue = -1;
int endOfInput = -1;
int topEvaluation = -1;
int topConversion = -1;

///Operator stack functions///
int isOperatorStackEmpty(void){ //Check if the stack is empty, 1 if true, 0 if false
    
    if(topOperator == -1){
        return 1;
    } else{
        return 0;
    }
    
}

int isOperatorStackFull(void){ //Check if the stack is full, 1 true, 0 if false
    
    if(topOperator == MAXSIZE){
        return 1;
    } else{
        return 0;
    }
}

char topOperatorStackValue(void){ // Return the top value of the stack
    
    return operatorStack[topOperator];
    
}

char popOperatorStack(void){ // Pop the top element of the stack
    
    char topElement;
    
    if(!isOperatorStackEmpty()){
        topElement = operatorStack[topOperator];
        topOperator = topOperator-1;
        return topElement;
    } else{
        printf("Stack is empty\n");
    }
    return 0;
}

char pushOperatorStack(char pushOperatorValue){ //Push the value onto the top element of the stack
    
    if(!isOperatorStackFull()){
        topOperator = topOperator+1;
        operatorStack[topOperator] = pushOperatorValue;
    } else{
        printf("Stack is full\n");
    }
    return 0;
    
}

void clearOperatorStack(void){
    
    for(int i = 0; i <= topOperator; i++){
        operatorStack[i] = 0;
        
    }
    
    topOperator = -1;
}

///////Output que functions///////

int isOutputQueEmpty(void){ //Check if the stack is empty, 1 if true, 0 if false
    
    if(endOfRPNOutputQue == -1){
        return 1;
    } else{
        return 0;
    }
    
}

int isOutputQueFull(void){ //Check if the stack is full, 1 true, 0 if false
    
    if(endOfRPNOutputQue == MAXSIZE){
        return 1;
    } else{
        return 0;
    }
}

char addToOutputQue(char queValue){ //Add value to end of output que
    
    if(!isOutputQueFull()){
        endOfRPNOutputQue = endOfRPNOutputQue+1;
        RPNQue[endOfRPNOutputQue] = queValue;
    } else{
        printf("Que is full\n");
    }
    return 0;
}

char popOutputQue(void){ // Clear the output que
    
    char topElement;
    
    while(!isOutputQueFull()){
        topElement = RPNQue[endOfRPNOutputQue];
        endOfRPNOutputQue = endOfRPNOutputQue-1;
        return topElement;
    }
    
    return 0;
}

void clearOutputQue(void){
    
    for(int i = 0; i <= endOfRPNOutputQue; i++){
        RPNQue[i] = 0;
        
    }
    
    endOfRPNOutputQue = -1;
}


///Add keypad input into infix stack string functions///

int isInputStringFull(void){ //Check if the stack is full, 1 true, 0 if false
    
    if(endOfInput == MAXSIZE){
        return 1;
    } else{
        return 0;
    }
}

void infixInput(char keypadValue){ //Add input character to end of input string
    
    if(!isOutputQueFull()){
        endOfInput = endOfInput+1;
        InputString[endOfInput] = keypadValue;
    } else{
        printf("String is full\n");
    }
}

void clearInputString(void){
    
    for(int i = 0; i <= endOfInput; i++){
        InputString[i] = 0;
        
    }
    
    endOfInput = -1;
}


//RPN stacks////

int isEvaluationStackEmpty(void){ //Check if the stack is empty, 1 if true, 0 if false
    
    if(topEvaluation == -1){
        return 1;
    } else{
        return 0;
    }
    
}

int isEvaluationStackFull(void){ //Check if the stack is full, 1 true, 0 if false
    
    if(topEvaluation == MAXSIZE){
        return 1;
    } else{
        return 0;
    }
}

double topEvaluationStackValue(void){ // Return the top value of the stack
    
    double stackValue = evaluationStack[topEvaluation];
    return stackValue;
    
}

char popEvaluationStack(void){ // Pop the top element of the stack
    
    char topElement;
    
    if(!isEvaluationStackEmpty()){
        topElement = evaluationStack[topEvaluation];
        topEvaluation= topEvaluation-1;
        return topElement;
    } else{
        printf("Stack is empty\n");
    }
    return 0;
}

double pushEvaluationStack(double pushEvaluationValue){ //Push the converted double value onto the top element of the stack
    
    if(!isEvaluationStackFull()){
        topEvaluation = topEvaluation+1;
        evaluationStack[topEvaluation] = pushEvaluationValue;
    } else{
        printf("Stack is full\n");
    }
    return 0;
    
}

void clearEvaluationStack(void){
    
    for(int i = 0; i <= topEvaluation; i++){
        evaluationStack[i] = 0;
        
    }
    
    topEvaluation = -1;
}



void pushDoubleConversionStack(char pushConversionValue){ //Push the value onto the top element of the stack
    
        topConversion = topConversion+1;
        doubleConversionStack[topConversion] = pushConversionValue;

}

void clearDoubleConversionStack(void){
    
    for(int i = 0; i <= topConversion; i++){
        doubleConversionStack[i] = 0;
        
    }
    
    topConversion = -1;
}


//Infix to reverse polish notation functions//

int isOperator(char currentToken){
    
    switch(currentToken){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            return 1; //Return 1 if currentToken is an operator (1 = true);
            break;
        default:
            return 0; //Return 0 if not
            break;
            
    }

}

int operatorPriority(char operatorInput){ //Return the operator's priority
    
    int priority = 0;
    
    switch(operatorInput){
        case '^':
            priority = 4;
            break;
        case '*':
        case '/':
        case '%':
            priority = 3;
            break;
        case '+':
        case '-':
            priority = 2;
            break;
        case '(':
            priority = 1;
            break;
    }
    
    
    return priority;
    
}

int operatorAssociativity(char operatorInput){//Return the operators associativity
    
    switch (operatorInput) {
        case '^':
            return RIGHT_ASSOCIATIVE;
            break;
        case '*':
        case '/':
        case '+':
        case '-':
            return LEFT_ASSOCIATIVE;
            break;
        default:
            return 0;
            break;
    }
    
    
}


void convertInfixToRPN(void){ //Conversion of the input string to reverse polish notation by means of the shunting yard algorithm, this allows for calculation in line with BODMAS.

    
    for(int i = 0; i <= endOfInput; i++){ //Iterate through the input string, empty space is added between each operand and operator so as to allow for distinction between multi digit and floating point numbers when evaluating the RPN string.
        
        const char currentToken = InputString[i];
        
        if(isdigit(currentToken) || currentToken == '.'){
            
            if(isOperator(RPNQue[endOfRPNOutputQue])){
                addToOutputQue(' ');
            }
            addToOutputQue(currentToken);
        }
        
        
        else if(isOperator(currentToken)){
            
            addToOutputQue(' ');
            
            while(
                  ( (operatorPriority(topOperatorStackValue()) > operatorPriority(currentToken)) && (operatorAssociativity(currentToken) == RIGHT_ASSOCIATIVE) )
                  ||
                  ( (operatorPriority(topOperatorStackValue()) >= operatorPriority(currentToken)) && (operatorAssociativity(currentToken) == LEFT_ASSOCIATIVE) )
                 ){
                
                addToOutputQue(topOperatorStackValue());
                popOperatorStack();
                
            }
            
            pushOperatorStack(currentToken);
            
        }
        
        else if(currentToken == '('){
            
            pushOperatorStack(currentToken);
            
        }
        
        else if(currentToken == ')'){
            
            while(topOperatorStackValue() != '('){
                
                addToOutputQue(' ');
                addToOutputQue(topOperatorStackValue());
                popOperatorStack();
                
            }
            
            popOperatorStack(); //Discard left bracket, stack should be empty here
        }
        
        
    }

    
    while(!isOperatorStackEmpty()){
        
        addToOutputQue(' ');
        addToOutputQue(topOperatorStackValue());
        popOperatorStack();
        
    }
    

    
    
}


//RPN evaluation functions//
double performOperation(char operator, double operand1, double operand2){
    
    double result = 0;
    
    switch(operator){
        case '+':
            result = (operand1 + operand2);
            break;
        case '-':
            result = (operand1 - operand2);
            break;
        case '*':
            result = (operand1 * operand2);
            break;
        case '/':
            result = (operand1 / operand2);
            break;
        case '^':
            result = pow(operand1, operand2);
            break;
        default:
            break;
            
            
    }
    
    return result;
    
}

double evaluateRPN(void){// Evaluates the reverse polish notation string
    
    double result = 0;
    
    for (int i = 0; i <= RPNQue[i]; i++){
        
        char currentTokenRPN = RPNQue[i];
        
        if(isOperator(currentTokenRPN)){
         
            double num2 = (topEvaluationStackValue());
            popEvaluationStack();
            double num1 = (topEvaluationStackValue());
            popEvaluationStack();
            result = performOperation(currentTokenRPN, num1, num2);
            pushEvaluationStack(result);
            
            
        }
        else if (isdigit(currentTokenRPN) || currentTokenRPN == '.'){
            
            pushDoubleConversionStack(currentTokenRPN);
            
        }
        else if (currentTokenRPN == ' ' && !isOperator(RPNQue[i-1])){// If a space is encountered and the previous char in the stack stack is not an operator, then convert the string in the double conversion stack to a double and add it to the evaluation stack, then clear the double conversion stack.
            
            
            double convertedValue = atof(doubleConversionStack);
            pushEvaluationStack(convertedValue);
            clearDoubleConversionStack();
            
        }
    
    }
    
    popEvaluationStack();
    
    return result;
    
}


double calculate(){ //Calculate function to call in main, return result of infix input expression
    
    convertInfixToRPN();
    double result = evaluateRPN();
    return result;
    
}

void clearAllCalculatorStacks(void){ //Clear all stacks, call when 'Clear' button is pressed on calculator
    
    clearOperatorStack();
    clearOutputQue();
    clearInputString();
    clearEvaluationStack();
    clearDoubleConversionStack();
    
}






/*int main(int argc, const char * argv[]) {
    
    infixInput('8');
    infixInput('1');
    infixInput('-');
    infixInput('3');
    infixInput('^');
    infixInput('(');
    infixInput('3');
    infixInput('/');
    infixInput('5');
    infixInput('1');
    infixInput(')');
    infixInput('(');
    infixInput('3');
    infixInput('5');
    infixInput('^');
    infixInput('2');
    infixInput('.');
    infixInput('3');
    infixInput(')');
    infixInput('/');
    infixInput('(');
    infixInput('3');
    infixInput('^');
    infixInput('4');
    infixInput(')');
    infixInput('-');
    infixInput('(');
    infixInput('6');
    infixInput('+');
    infixInput('4');
    infixInput(')');
    
    convertInfixToRPN();
    
    for (int i = 0; i <= endOfRPNOutputQue; i++){
        char toPrint = RPNQue[i];
    
        printf("%c", toPrint);
    }
    
    printf("  = %lf\n", evaluateRPN());


    
}*/
