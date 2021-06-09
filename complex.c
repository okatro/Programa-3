/* *****************************************************************
* complex.c
* Performs the following binary operations with complex numbers:
*   - Addition        z = z1 + z2
*   - Substraction    z = z1 - z2
*   - Multiplication  z = z1 x z2
*   - Division        z = z1 / z2
*
*
* Author: Mauricio Matamoros
* License: MIT
*
* *****************************************************************/

/* COMPILER DIRECTIVES ******************************************/
#include <stdlib.h>
#include <stdio.h>

/* STRUCTURES AND GLOBALS ***************************************/
/**
 * Defines the structure of a complex number
 */
struct {
	double re;
	double im;
} typedef complex;

/* PROTOTYPES ***************************************************/
/**
 * Adds two complex numbers as z = z1 + z2
 * @param Left-hand operand z1
 * @param Right-hand operand z2
 * @return The sum of the provided complex numbers
 */
complex zadd(complex z1, complex z2);

/**
 * Substracts two complex numbers as z = z1 - z2
 * @param Left-hand operand z1
 * @param Right-hand operand z2
 * @return The difference of the provided complex numbers
 */
complex zsub(complex z1, complex z2);

/**
 * Multiplies two complex numbers as z = z1 * z2
 * @param Left-hand operand z1
 * @param Right-hand operand z2
 * @return The product of the provided complex numbers
 */
complex zmul(complex z1, complex z2);

/**
 * Divides a complex number z1 by another z2 as in z = z1 / z2
 * @param Left-hand operand z1
 * @param Right-hand operand z2
 * @return The cocient of the provided complex numbers
 */
complex zdiv(complex z1, complex z2);

/**
 * Attempts to read a complex number from an ANSI-C string
 * @param The string containing a complex number
 * @param A pointer to a complex datatype where the values will be written.
 *        It yields z=0+0i when the conversion fails.
 * @return 1 if the conversion succeeded, zero otherwise.
 */
int parse(char* s, complex *z);

complex zpot(complex z1, int pot);



/* MAIN *********************************************************/
int main(int argc, char** argv){
	complex z;       /* Stores the result */
	complex z1, z2;  /* Store the operands z1 and z2 */

	// Program needs exactly 3 arguments: z1 op z2
	if(argc != 4){
		printf("Usage %s re+imi op re2+im2i\n",argv[0]);
		return -1;
	}

	// Read operands z1 and z2
	if(!parse(argv[1], &z1)){
		printf("Unrecognized parameter \"%s\"\nUsage %s re+imi op re2+im2i\n",argv[1],argv[0]);
		return -1;
	}
	if(!parse(argv[3], &z2)){
		printf("Unrecognized parameter \"%s\"\nUsage %s re+imi op re2+im2i\n",argv[3],argv[0]);
		return -1;
	}

	// Read operator op. We care only about first character
	switch(argv[2][0]){
		case '+':
			z = zadd(z1, z2); break;
		case '-':
			z = zsub(z1, z2); break;
		case 'x':
		case '*': // <- * special char in bash needs to be escaped, use x instead
			z = zmul(z1, z2); break;
		case '/':
			z = zdiv(z1, z2); break;
		case '^':
			z = zpot(z1, (int)z2.re); break;
		default:
			printf("Unrecognized parameter \"%s\"\nUsage %s re+imi op re2+im2i\n",argv[2],argv[0]);
			return -1;
	}
	printf("%0.4f%+0.4fi\n", z.re, z.im);
	return 0;
}

/* FUNCTION DEFINITIONS *****************************************/

int parse(char* s, complex *z){
	char* bcc = s;
	char* cc;
	// init z
	z->re = 0; z->im = 0;
	if (s == NULL) return 0;
	// Convert real part
	z->re = strtod(bcc, &cc);
	if(*cc == '\0') return 1;
	// Convert imaginary part
	if ((*cc != '+') && (*cc != '-')) return 0;
	bcc = cc;
	z->im = strtod(bcc, &cc);
	if(*cc == 'i') return 1;
	return 0;
}

complex zadd(complex z1, complex z2){
	complex result = {z1.re + z2.re , z1.im + z2.im};

	return result;
}

complex zsub(complex z1, complex z2){
	complex result = {z1.re - z2.re , z1.im - z2.im};

	return result;
}

complex zmul(complex z1, complex z2){
	double PR = 0, PI = 0;

	PR = (z1.re * z2.re) - (z1.im * z2.im);

	PI = (z1.re * z2.im) + (z1.im * z2.re);

	complex result = {PR , PI};

	return result;
}

complex zdiv(complex z1, complex z2){
	complex Mul = {z2.re , -z2.im};

	complex U = zmul(z1 , Mul);
	double D = zmul(z2 , Mul).re;

	complex result = {U.re/D , U.im/D};

	return result;

}

complex zpot(complex z1, int pot){
	printf("pot %d\n", pot);

	complex result = z1;
	
	for(int i = 0 ; i < pot ; ++i){
		double PR = 0, PI = 0;

		PR = (z1.re * result.re) - (z1.im * result.im);

		PI = (z1.re * result.im) + (z1.im * result.re);

		result.re = PR;
		result.im = PI;

	}

	return result;
}