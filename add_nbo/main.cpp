#include <stddef.h> //for size_t
#include <stdint.h> //for uint32_t
#include <stdio.h> //for printf
#include <netinet/in.h> //for ntoh

int main(int argc, char *argv[])
{
	// set file path
	const char* thousandFile = argv[1];
	const char* fiveHundredFile = argv[2];
	
	// valriables to read files
	uint32_t thousandValue;
	uint32_t fiveHundredValue;

	// open thousand.bin
	FILE *thousandFilePtr = fopen(thousandFile, "rb");
	if (!thousandFilePtr){
		perror("Error opening file: ");
		fclose(thousandFilePtr);
		return 1;
	}

    	// open five-hundred.bin
    	FILE* fiveHundredFilePtr = fopen(fiveHundredFile, "rb");
    	if (!fiveHundredFilePtr) {
    		perror("Error opening file: ");
		return 1;
	    }
	
	fread(&thousandValue,sizeof(thousandValue),1,thousandFilePtr);
	fclose(thousandFilePtr);
	fread(&fiveHundredValue, sizeof(fiveHundredValue), 1, fiveHundredFilePtr);
	fclose(fiveHundredFilePtr);

	// Convert values from network byte order to host byte order
	uint32_t hostValue1 = ntohl(thousandValue);
	uint32_t hostValue2 = ntohl(fiveHundredValue);
	
	// Calculate the sum
    	uint32_t sum = hostValue1 + hostValue2;

	// Print the result in decimal and hexadecimal
	printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n",
	hostValue1, hostValue1, hostValue2, hostValue2, sum, sum);
	
	return 0;
}
