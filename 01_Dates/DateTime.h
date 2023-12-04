#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
using namespace std;
/// <summary>
/// Gestione di date e orari.
/// </summary>
class DateTime
{
private:
	int hours;
	int minutes;
	int seconds;
	int year;
	int month;
	int day;
	DateTime() :DateTime(0, 0, 0, 0, 0, 0) {}
	DateTime(int y, int m, int d, int h, int n, int s) :
		year(y), month(m), day(d), hours(h), minutes(n), seconds(s) {}
public:
	const string ISO_DATE_FORMAT = "DATE_ISO_FORMAT";

	static DateTime now() {
		time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
		tm t; localtime_s(&t, &now);
		return DateTime(t.tm_year + 1900, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
	}
	static bool isLeapYear(int);
	static bool isValidDate(int, int, int);
	static bool isValidTime(int, int, int);

	inline int getYear() const { return year; }
	inline int getMonth()const { return month; }
	inline int getDay() const { return day; }
	inline int getHour() const { return hours; }
	inline int getMinute() const { return minutes; }
	inline int getSecond() const { return seconds; }

	void setTime(int, int, int);
	void setDate(int, int, int);

	void addHours(int);
	void addMinutes(int);
	void addSeconds(int);
	void addYears(int);
	void addMonths(int);
	void addDays(int);
	void endOfMonth();


	string toISODate() const;
	string toString() const;
	string toString(string format) const;

	friend ostream& operator << (ostream& s, const DateTime d) { return s << d.toISODate(); }
	friend DateTime operator+(const DateTime first, string timespan);
	friend DateTime operator-(const DateTime first, string timespan);

	friend class DateBuilder;
};

class DateBuilder {
	int y, m, d, h, n, s;
public:
	DateBuilder& withYear(int y) { this->y = y; return *this; }
	DateBuilder& withMonth(int m) { this->m = m; return *this; }
	DateBuilder& withDay(int d) { this->d = d; return *this; }
	DateBuilder& withHour(int h) { this->h = h; return *this; }
	DateBuilder& withMinute(int m) { this->n = n; return *this; }
	DateBuilder& withSecond(int s) { this->s = s; return *this; }
	DateTime build() {
		if (DateTime::isValidDate(y, m, d) && DateTime::isValidTime(h, n, s))
			return DateTime(y, m, d, h, n, s);
		throw "Invalid date";
	}
};


string operator""_years(unsigned long long y);
string operator""_months(unsigned long long y);
string operator""_days(unsigned long long y);
string operator""_h(unsigned long long y);
string operator""_m(unsigned long long y);
string operator""_s(unsigned long long y);
