default:
	c++ -Wall -ggdb user_data.cpp simplex.cpp main.cpp -o Simplex
clean:
	rm Simplex table.txt
