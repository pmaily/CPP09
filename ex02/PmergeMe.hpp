#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <list>
# include <vector>
# include <iostream>
# define K 28

template< class Container = std::list<int> >
class PmergeMe{
	private:

		Container	value_list;
	
	public:

		typedef typename Container::iterator	iterator;

		PmergeMe(void) {}

		PmergeMe(const PmergeMe& src) {*this = src;}

		~PmergeMe(void) {}

		PmergeMe&	operator=(const PmergeMe& src)
		{
			value_list = src.value_list;
			return *this;
		}

		void	addValue(int value)
		{
			value_list.push_back(value);
		}
		
		Container insertionSort(iterator begin, iterator end)
		{
			Container list(begin, end);
			Container new_list;
			iterator it;

			new_list.push_back(list.front());
			list.erase(list.begin());
			it = new_list.end();
			while (list.size())
			{
				it--;
				if (*it >= list.front() && it == new_list.begin())
				{
					new_list.insert(it, list.front());
					list.erase(list.begin());
					it = new_list.end();
				}
				else if (*it < list.front())
				{
					it++;
					new_list.insert(it, list.front());
					list.erase(list.begin());
					it = new_list.end();
				}
			}

			return new_list;
		}

		void sort(void)
		{
			value_list = sortValue(value_list.begin(), value_list.end());
		}

		Container mergeSort(Container list1, Container list2)
		{
			Container new_list;

			while (list1.size() && list2.size())
			{
				if (list1.front() < list2.front())
				{
					new_list.push_back(list1.front());
					list1.erase(list1.begin());
				}
				else
				{
					new_list.push_back(list2.front());
					list2.erase(list2.begin());
				}
			}
			if (!list1.empty())
				new_list.insert(new_list.end(), list1.begin(), list1.end());
			else if (!list2.empty())
				new_list.insert(new_list.end(), list2.begin(), list2.end());
			return new_list;
		}

		Container	sortValue(iterator start, iterator end)
		{
			Container	right;
			Container	left;
			iterator	middle = start;
			int			size = std::distance<iterator>(start, end);

			if (size > K)	
			{
				for (int i = 0; i < size / 2; i++)
					middle++;
				right = sortValue(start, middle);
				left = sortValue(middle, end);
				return mergeSort(right, left);
			}
			else
				return insertionSort(start, end);
	
		}

		void	displayValue(void)
		{
			for(iterator it = value_list.begin(); it != value_list.end(); it++)
				std::cout << " " << *it << std::flush;
		}

};

#endif