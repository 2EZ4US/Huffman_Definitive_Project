#include "header.h"

int main() {
	INTEGER choiceNumber;

	printf("0 to Compress\n1 to Decompress: ");
	scanf("%lld", &choiceNumber);	

	if(!choiceNumber) {
		Compress_File();
	} else {
		Decompress_File();
	}
	return 0;
}
