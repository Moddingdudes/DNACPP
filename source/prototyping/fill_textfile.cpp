#include <fstream>
#include <cstdlib>

int main() {
	srand(time(NULL));
	std::fstream file;
	file.open("my_dna.txt", std::ios::out);

	int randomNumber;

	for (int i=0; i<27401; i++) {
		randomNumber = rand() & 3;
		switch(randomNumber) {
			case 0:
				file << 'A';
				break;
			case 1:
				file << 'C';
				break;
			case 2:
				file << 'G';
				break;
			case 3:
				file << 'T';
				break;
		}
	}

	return 0;
}
