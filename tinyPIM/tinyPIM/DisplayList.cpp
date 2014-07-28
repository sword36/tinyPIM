#include "DisplayList.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <iterator>
#include <algorithm>

DisplayList::DisplayList(int linesPerScreen)
	:linesPerScreen_(linesPerScreen)
{
	reset();
}


DisplayList::~DisplayList(void)
{
}

void DisplayList::reset()
{
	cache_.clear();
	cachedFirst_ = false;
	cachedLast_ = false;
	firstVisibleIdx_ = 0;
}

void DisplayList::fillCacheBwd(int start, int numNeeded)
{
	int startID = 0;
	if (cache_.empty())
		cachedLast_ = true;
	else 
	{
		assert(start < cache_.size());
		startID = cache_.front();
	}
	int recordTillStart = start;
	if (!cachedFirst_ && recordTillStart < cache_.size())
	{
		std::vector<int> moreRecords;
		cachedFirst_ = fetchMore(start, - (numNeeded -  recordTillStart), moreRecords);
		std::copy(moreRecords.rbegin(), moreRecords.rend(), std::front_inserter(cache_));

	}
}

void DisplayList::fillCacheFwd(int start, int numNeeded)
{
	int startID = 0;
	if (cache_.empty())
		cachedFirst_ = true;
	else
	{
		assert(start < cache_.size());
		startID = cache_.back();
	}
	int recordsTillEnd = cache_.size() - start;
	if (!cachedLast_ && recordsTillEnd < numNeeded)
	{
		std::vector<int> moreRecords;
		cachedLast_ = fetchMore(start, numNeeded - recordsTillEnd, moreRecords);
		std::copy(moreRecords.begin(), moreRecords.end(), 
					std::back_inserter(cache_));
		firstVisibleIdx_ += moreRecords.size();
	}
}

void DisplayList::display()
{
	fillCacheFwd(firstVisibleIdx_, linesPerScreen_);
	if (cache_.empty())
	{
		std::cout << "========No records selected============" << std::endl;
	return;
	}
	int recsToShow = std::min(linesPerScreen_, int(cache_.size() - firstVisibleIdx_));
	if (atStart())
		std::cout << "================Start of list===========\n";
	cache_t::iterator start = cache_.begin() + firstVisibleIdx_;
	cache_t::iterator finish = start + recsToShow;
	for (cache_t::iterator i = start; i != finish; ++i)
	{
		int lineNum = i - start + 1;
		std::cout << std::setw(2) << std::setfill(' ') <<
			std::right << std::dec << lineNum << ": ";
		displayRecord(*i); 
		std::cout << std::endl;
		if (atEnd())
			std::cout << "===========End of records============";
		std::cout << std::endl;
	}
}

void DisplayList::pageDown()
{
	if (atEnd())
		return;
	fillCacheFwd(firstVisibleIdx_, 2 * linesPerScreen_);
	if (!atEnd())
		firstVisibleIdx_ += linesPerScreen_;
	return;
}

void DisplayList::pageUp()
{
	if (atStart())
		return;
	fillCacheBwd(firstVisibleIdx_, linesPerScreen_);
	firstVisibleIdx_ = std::max(firstVisibleIdx_ - linesPerScreen_, 0);
}

void DisplayList::toStart()
{
	if (cachedFirst_)
		firstVisibleIdx_ = 0;
	else 
		reset();
}

bool DisplayList::atEnd()
{
	return (cachedLast_ && (cache_.size()-firstVisibleIdx_ <= linesPerScreen_));
}

bool DisplayList::atStart()
{
	return (cachedFirst_ && (firstVisibleIdx_ == 0));
}

void DisplayList::scrollToTop(int recordID)
{
	assert(recordID != 0);
	cache_t::iterator found = std::find(cache_.begin(), cache_.end(), recordID);
	if (found == cache_.end())
	{
		reset();
		firstVisibleIdx_ = 0;
		cache_.push_back(recordID);
	}
	else 
		firstVisibleIdx_ = found - cache_.begin();
	fillCacheFwd(firstVisibleIdx_, linesPerScreen_);
}

int DisplayList::screenRecord(int n) const
{
	if (firstVisibleIdx_ + n >= cache_.size())
		return 0;
	else
		return cache_[firstVisibleIdx_ + n];
}

int DisplayList::selectRecord()
{
	while (std::cin.good())
	{
		int maxSelection = std::min(linesPerScreen_, 
			int(cache_.size() - firstVisibleIdx_));
		if (maxSelection <= 0)
		{
			std::cout << "No records to select\n";
			return 0;
		}
		std::cout << "Choose a record number between 1 and "<<
			maxSelection <<"\nRecord number (0 to cancel)?";
		unsigned selection = 0;
		std::cin >> selection;
		if (std::cin.fail())
		{
			if (std::cin.bad() || std::cin.eof())
				break;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalit selection, please, try again\n\n";
			continue;
		}
		std::cin.ignore(1000, '\n');
		if (selection == 0)
			return 0;
		if (1 <= selection && selection <= maxSelection)
			return cache_[firstVisibleIdx_ + selection - 1];
		else
			std::cout <<"Invalid selection, try again\n\n";
		return 0;
	}
}