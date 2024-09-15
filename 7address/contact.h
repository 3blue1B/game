#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define Default 3
#define Increase 2
#define max_name 20
#define max_sex 10
#define max_tele 12
#define max_addr 30
typedef struct PeoInfo
{
	char name[max_name];
	int age;
	char sex[max_sex];
	char tele[max_tele];
	char addr[max_addr];
}PeoInfo;
typedef struct Contact
{
	PeoInfo* data;
	int count;
	int capacity;
}Contact;

void InitContact(Contact* pc);
void AddContact(Contact* pc);
void ShowContact(const Contact* pc);
void DelContact(Contact* pc);
void SearchContact(Contact* pc);
void ModifyContact(Contact* pc);
void SortContact(Contact * pc);
void DestroyContact(Contact* pc);
void SaveContact(const Contact* pc);
void LoadContact(Contact* pc);



