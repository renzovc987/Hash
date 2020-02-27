#include <bits/stdc++.h>
using namespace std;

int NextPrime(int a)
{
    int i, j, count, num;
    for (i = a + 1; 1; i++)
    {
        for (j = 2, count = 0; j <= i; j++)
        {
            if (i%j == 0)
            {
                count++;
            }
        }
        if (count == 1)
        {
            return i;
            break;
        }
    }
}

int doublehash(int x, int p){
	return p-(x%p);
}

template <typename Key>
class hashh
{
public:
	size_t operator() ( const Key & k ) const;
};

template <>
class hashh<int>
{
public:
	size_t operator() ( const int & k ) const{
		return k;
	}
};

template <>
class hashh<string>
{
public:
	size_t operator()( const string & key )
	{
		size_t hashVal = 0;
		for( char ch : key )
			hashVal = 37 * hashVal + ch;
		return hashVal;
	}

};

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable( int size = 101 ): theLists( NextPrime( size ) ){
		makeEmpty( );
	}

	bool contains( const HashedObj & x ) const{
		auto & whichList = theLists[ myhash( x ) ];
		return find( begin( whichList ), end( whichList ), x ) != end( whichList );
	}

	void makeEmpty( ){
		for( auto & thisList : theLists )
			thisList.clear();
	}

	bool insert( const HashedObj & x ){
		auto & whichList = theLists[ myhash( x ) ];
		if( find( begin( whichList ), end( whichList ), x ) != end( whichList ) )
			return false;
		whichList.push_back( x );

		// Rehash; see Section 5.5
		if( ++currentSize > theLists.size( ))
			rehash( );
		return true;
	}

	//bool insert( HashedObj && x );
	bool remove( const HashedObj & x ){
		auto & whichList = theLists[ myhash( x ) ];
		auto itr = find( begin( whichList ), end( whichList ), x );

		if( itr == end( whichList ) )
			return false;

		whichList.erase( itr );
		--currentSize;
		return true;
	}




private:

	vector<list<HashedObj>> theLists;
	int currentSize;

	void rehash( ){
		vector<list<HashedObj>> oldLists = theLists;
		theLists.resize( NextPrime( 2 * theLists.size( ) ) );
		for( auto & thisList : theLists )
			thisList.clear( );
		currentSize = 0;
		for( auto & thisList : oldLists )
			for( auto & x : thisList )
				insert( std::move( x ) );
	}

	size_t myhash( const HashedObj & x ) const{
		static hashh<HashedObj> hf;
		return hf( x ) % theLists.size( );
	}
};

int main(){

	HashTable<int> ht;
	ht.insert(417);//residuo 5
	ht.insert(930);//residuo 3
	ht.insert(314);//residuo 5
	ht.insert(110);//residuo 7
	ht.insert(107);//residuo 0
	ht.insert(722);//residuo 1
	ht.insert(825);//residuo 1
	ht.insert(524);//residuo 7
	ht.insert(107);//residuo 7
	ht.remove(722);

	cout<<ht.contains(110)<<endl;
	cout<<ht.contains(310)<<endl;
	cout<<ht.contains(722)<<endl;


	return 0;
}
