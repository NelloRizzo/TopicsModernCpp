#include "DateTime.h"
#include <iomanip>
#include <format>
using namespace std;

bool DateTime::isLeapYear(int y)
{
	return y % 4 == 0 && y % 400 != 0;
}

bool DateTime::isValidDate(int y, int m, int d)
{
	if (m < 1 || m > 12) return false;
	int MONTH_DAYS[] = { 31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return d > 0 && d <= MONTH_DAYS[m - 1];
}

bool DateTime::isValidTime(int h, int m, int s)
{
	return h > -1 && h < 24 && m > -1 && m < 60 && s > -1 && s < 60;
}

void DateTime::setTime(int h, int m, int s)
{
	if (isValidTime(h, m, s))
	{
		hours = h;
		minutes = m;
		seconds = s;
	}
}

void DateTime::setDate(int y, int m, int d)
{
	if (y < 100) y += 2000;
	if (isValidDate(y, m, d)) {
		year = y;
		month = m;
		day = d;
	}
}

void DateTime::addHours(int h)
{
	int hh = hours;
	int incr = h > 0 ? 1 : -1;
	h = abs(h);
	while (h > 0) {
		hh += incr;
		if (hh < 0) {
			addDays(-1);
			hh = 59;
		}
		if (hh > 23) {
			addDays(1);
			hh = 0;
		}
		h--;
	}
	hours = hh;
}

void DateTime::addMinutes(int m)
{
	int mm = minutes;
	int incr = m > 0 ? 1 : -1;
	m = abs(m);
	while (m > 0) {
		mm += incr;
		if (mm < 0) {
			addHours(-1);
			mm = 59;
		}
		if (mm > 59) {
			addHours(1);
			mm = 0;
		}
		m--;
	}
	minutes = mm;
}

void DateTime::addSeconds(int s)
{
	int ss = seconds;
	int incr = s > 0 ? 1 : -1;
	s = abs(s);
	while (s > 0) {
		s += incr;
		if (s < 0) {
			addMinutes(-1);
			s = 59;
		}
		if (s > 59) {
			addMinutes(1);
			s = 0;
		}
		s--;
	}
	seconds = ss;
}

void DateTime::addYears(int y)
{
	bool remember_february = day == 29 && month == 2;
	year += y;
	if (remember_february && !isLeapYear(year))
	{
		month = 3;
		day = 1;
	}
}

void DateTime::addMonths(int m)
{
	int mm = month;
	int incr = m > 0 ? 1 : -1;
	m = abs(m);
	while (m > 0) {
		mm += incr;
		if (mm < 1) {
			addYears(-1);
			mm = 12;
		}
		if (mm > 12) {
			addYears(1);
			mm = 1;
		}
		m--;
	}
	month = mm;
}

void DateTime::addDays(int d)
{
	int dd = day;
	int incr = d > 0 ? 1 : -1;
	d = abs(d);
	int MONTH_DAYS[] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	while (d > 0) {
		if (isLeapYear(year)) MONTH_DAYS[1] = 29; else MONTH_DAYS[1] = 28;
		dd += incr;
		if (dd < 1) {
			addMonths(-1);
			dd = MONTH_DAYS[month - 1];
		}
		if (dd > MONTH_DAYS[month - 1]) {
			addMonths(1);
			dd = 1;
		}
		d--;
	}
	day = dd;
}

void DateTime::endOfMonth()
{
	DateTime d;
	d.setDate(year, month, 1);
	d.addMonths(1);
	d.addDays(-1);
	year = d.year;
	month = d.month;
	day = d.day;
}


string DateTime::toISODate() const
{
	stringstream ss;
	ss << setfill('0') << setw(4) << year << '-' << setw(2) << month << '-' << setw(2) << day << 'T' << setw(2) << hours << ':' << setw(2) << minutes << ':' << setw(2) << seconds;
	return ss.str();
}

string DateTime::toString() const
{
	return toString(ISO_DATE_FORMAT);
}

string DateTime::toString(string format) const
{
	if (format == ISO_DATE_FORMAT) return toISODate();
	stringstream ss;
	const char* fmt = format.c_str();
	bool skip = false;
	while (*fmt) {
		if (*fmt == '^') {
			skip = !skip; fmt++;
		}
		if (skip) {
			ss << *fmt++;
		}
		else {
			switch (*fmt) {
			case 'M':
				ss << setw(2) << setfill('0');
				[[fallthrough]];
			case 'm':
				ss << month;
				break;
			case 'y':
				ss << year % 100;
				break;
			case 'Y':
				ss << year;
				break;
			case 'D':
				ss << setw(2) << setfill('0');
				[[fallthrough]];
			case 'd':
				ss << day;
				break;
			case 'H':
				ss << setw(2) << setfill('0');
				[[fallthrough]];
			case 'h':
				ss << hours;
				break;
			case 'A':
				ss << setw(2) << setfill('0');
				[[fallthrough]];
			case 'a': {
				int h = hours > 13 ? hours - 12 : hours;
				ss << h << (hours > 11 ? "PM" : "AM");
			}
					break;
			case 'I':
				ss << setw(2) << setfill('0');
				[[fallthrough]];
			case 'i':
				ss << minutes;
				break;
			case 'S':
				ss << setw(2) << setfill('0');
				[[fallthrough]];
			case 's':
				ss << seconds;
				break;
			default:
				ss << *fmt;
			}
			fmt++;
		}
	}
	return ss.str();
}

static int readInt(const char* t) {
	string s;
	if (*t == '-') { s += '-'; t++; }
	while (*t >= '0' && *t <= '9') {
		s += *t;
		t++;
	}
	return atoi(s.c_str());
}

DateTime operator+(DateTime first, string timespan)
{
	DateTime result = first;
	const char* t = timespan.c_str();
	while (*t) {
		switch (*t)
		{
		case 'Y':
		case 'y':
			result.addYears(readInt(t + 1));
			break;
		case 'M':
		case 'm':
			result.addMonths(readInt(t + 1));
			break;
		case 'D':
		case 'd':
			result.addDays(readInt(t + 1));
			break;

		case 'H':
		case 'h':
			result.addHours(readInt(t + 1));
			break;
		case 'I':
		case 'i':
			result.addMinutes(readInt(t + 1));
			break;
		case 'S':
		case 's':
			result.addSeconds(readInt(t + 1));
			break;
		}
		t++;
	}
	return result;
}

DateTime operator-(DateTime first, string timespan)
{
	DateTime result = first;
	const char* t = timespan.c_str();
	while (*t) {
		switch (*t)
		{
		case 'Y':
		case 'y':
			result.addYears(-readInt(t + 1));
			break;
		case 'M':
		case 'm':
			result.addMonths(-readInt(t + 1));
			break;
		case 'D':
		case 'd':
			result.addDays(-readInt(t + 1));
			break;

		case 'H':
		case 'h':
			result.addHours(-readInt(t + 1));
			break;
		case 'I':
		case 'i':
			result.addMinutes(-readInt(t + 1));
			break;
		case 'S':
		case 's':
			result.addSeconds(-readInt(t + 1));
			break;
		}
		t++;
	}
	return result;
}

string operator""_years(unsigned long long y) {
	return format("Y{}", y);
}
string operator""_months(unsigned long long m) {
	return format("M{}", m);
}
string operator""_days(unsigned long long d) {
	return format("D{}", d);
}
string operator""_h(unsigned long long h) {
	return format("H{}", h);
}
string operator""_m(unsigned long long m) {
	return format("I{}", m);
}
string operator""_s(unsigned long long s) {
	return format("S{}", s);
}
