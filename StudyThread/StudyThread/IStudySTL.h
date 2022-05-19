#pragma once

class IStudyStl
{
public:
	virtual  void AddElement() = 0;
	virtual  void DeleteAllElement() = 0;
	virtual  void PrintAllElement() = 0;
	virtual  ~IStudyStl() {}
};
