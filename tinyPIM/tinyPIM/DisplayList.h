#pragma once
#include <vector>
#include <deque>

class DisplayList
{
public:
	DisplayList(int linesPerScreen = 15);
	virtual ~DisplayList(void);
	
	void display();
	void pageDown();
	void pageUp();
	void toStart();
	bool atStart();
	bool atEnd();
	void reset();
	int screenRecord(int n) const;
	void scrollToTop(int recordID);
	int selectRecord();
protected:
	virtual void displayRecord(int recordID) = 0;
	virtual bool fetchMore(int startID, int numRecords,
							std::vector<int>& result) = 0;
private:
	typedef std::deque<int> cache_t;
	int linesPerScreen_;
	cache_t cache_;
	bool cachedFirst_;
	bool cachedLast_;
	int firstVisibleIdx_;
	void fillCacheFwd(int start, int numNeeded);
	void fillCacheBwd(int start, int numnNeeded);

};

