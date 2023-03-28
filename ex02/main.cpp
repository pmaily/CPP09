#include "PmergeMe.hpp"
#include <cstdlib>
#include <cerrno>
#include <sys/time.h>

int	timestamp(struct timeval time)
{
	struct timeval	real_time;

	gettimeofday(&real_time, NULL);
	return ((real_time.tv_sec - time.tv_sec) * 1000000 + (real_time.tv_usec - \
				time.tv_usec));
}


int main(int ac, char **av)
{
	PmergeMe< std::vector<int> >	int_vector;
	PmergeMe< std::list<int> >		int_list;
	struct timeval					time;
	int								value;
	int								time_vect;
	int								time_list;
	char							*ptr;
	int size;

	if (ac < 2)
		return 1;
	for(int i = 1; i < ac; i++)
	{
		value = strtol(av[i], &ptr, 10);
		if (value < 0 || errno == ERANGE || (ptr && ptr[0]) || !av[i][0])
		{
			std::cerr << "Error: bad input" << std::endl;
			return 1;
		}
		int_vector.addValue(value);
		int_list.addValue(value);
		size = i;
	}
	std::cout << "Before:" << std::flush;
	int_list.displayValue();
	std::cout << std::endl;

	gettimeofday(&time, NULL);
	int_list.sort();
	time_list = timestamp(time);
	gettimeofday(&time, NULL);
	int_vector.sort();
	time_vect = timestamp(time);


	std::cout << "After:" << std::flush;
	int_vector.displayValue();
	std::cout << std::endl;

	std::cout << "Time to process a range of "<< size << " elements with std::vector: " << static_cast<float>(time_vect) / 1000.f << "ms" << std::endl;
	std::cout << "Time to process a range of "<< size << " elements with std::list: " << static_cast<float>(time_list) / 1000.f  << "ms" << std::endl;
}