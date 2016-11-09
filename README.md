# DeDup - A library to detect duplicate sets of integer values.
You are required to complete ALL tasks given below.

1. Create a library to detect duplicate sets of integer values. Two sets are considered duplicate when they contain the same number of items and their items are of the same value no matter what positions they are at.

> 	Example:
> 	
> 	1,2,3 is considered a duplicate of 2,1,3
> 	1,2,3 is not considered a duplicate of 1,2,3,1
> 	
> 	Library is required to provide:
> 	
> 	a) a way to accept a string representing a new set of values delimited by comma sign “,” (e.g. “1,2,3”) and return true/false if the given set is a duplicate of a set seen before,
> 	
> 	b) a way to return an information on number of duplicates and non-duplicates seen so far,
> 	
> 	c) a way to list members of the most frequent duplicate group seen so far,
> 	
> 	d) a way to return human readable report on list of invalid inputs seen so far.

2. What is your solution’s time and memory complexity? (Big O notation)

3. Create a set of unit tests to verify your solution. One of the unit tests is supposed to load records from enclosed input data file “input.txt” and verify your code correctly processes them.

4. Package your solution and your answers to the questions into a zip file and send them back to
 NCR for evaluation. Please let us know how long it took.

## Requirements
1. Boost 1.60
### Windows
1. Visual Studio 2015
2. Cygwin
3. GNU Make

### Linux
1. g++ 5.4

## Implementation
The code is implemented using the latest C++ standard. Boost has only been used to leverage the unit testing framework. The code has been build and tested using Visual C++ 2015 and g++ 5.4. The code is been distributed as a templated library that can easily be augmented in any of the existing code base or solution

## Building

### Windows

####Through IDE
Visual Studio 2015 Project and Solution file is bundled along with the submission that can be utilized to build and test the library. Binaries are copied in the standard distribution folder. There is a include and library dependency on boost, which needs to be change to refer to your BOOST_ROOT location. It is worth noting that %BOOST_ROOT%, may or may not be set in your environment, so you need to update the INCLUDE Directories and Library Directories to point to your respective boost root.

####Through Make System
Ensure BOOST_ROOT is set else `set BOOST_ROOT=C:\boost_1_60_0\boost_1_60_0`
From the project root folder run `make PLATFORM=windows`

**Note** By default, it build 32 bit binaries. To build 64 bit `make PLATFORM=windows BITNESS=x64`, but you need to ensure that your boost has been built as 64 bit.

### Linux
From the project root folder run `make PLATFORM=linux`

## Running

### Windows
An executable called DeDup.exe is generated under %PROJECT_ROOT%/Debug that when executed would run 5 sets of unit tests. 

You can also run it via the make file
`make run`

### Linux
An executable called DeDup is generated under %PROJECT_ROOT%/build that when executed would run 5 sets of unit tests

You can also run it via the make file
`make run`
## Algorithm Analysis

### What is your solution’s time and memory complexity? (Big O notation)

#### Insertion
DeDup is implemented as a Bag of Bags. A Bag is a subclass of std::map whose order of complexity is linear at best and logarithmic otherwise [N4567 23.4.4.2/4  [map.cons]](http://open-std.org/JTC1/SC22/WG21/docs/papers/2015/n4567.pdf). So if there are n comma separated list of m numbers then the order of complexity is O(N X M) at best and O(Nlog(N) X M log(M)) i.e. O(NMlog(N)log(M)) otherwise.

#### most_common
The `most_common` routine used a priority queue which is nothing but a heap queue in its implementation. Referring to the [SO Answer](http://stackoverflow.com/a/2974501/977038) as the standard is rather mum on this subject, the top() and pop() operations are O(1) and O(2*log(N)) respectively and push is O(log(N)). So, for the order of complexity for `most_common` is upper bound to O(Nlog(N)).

### Why I didn't use std::multiset? 
The interface of `std::multiset` is not quite compatible for our task, primarily as, it does not have an interface that can be queries to know occurrence as we iterate. Even, there is no standard way of grouping the unique elements with the occurrence count. 

### Why I didn't use std::unorderd_map?
The current implementation of `std::unorderd_map` uses the `std::hash` which doesn't support containers except `std::vector<bool>`. So, it may not be pragmatic to roll out a custom hash function and expect to scale better than `std::map`

