#pragma once
#pragma warning (disable:4996)
#include <iostream>
#include "Linked_List.h"
#include "FileClas.h"
#include <string.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

enum Menu {
	Add=1,
	Del,
	Show,
	Save,
	Load,
	Cls,
	EXIT= 99
};
