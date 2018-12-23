#pragma once

#include<string>
#include<stack>
#include<map>
#include<fstream>
#include"Lexer.h"

struct Parse_Node // Left-child Right-sibling Tree
{
	bool is_Terminal;
	int type;
	std::string data;
	Parse_Node* child; 
	Parse_Node* sibling;
};

namespace NT {
	enum {
		start, prog, prog_, decls, decls_, decl, words, words_, vtype, block, slist, slist_, stat, stat_, cond, cond_,
		expr, expr_, term, term_, fact
	};
}

namespace T {
	enum {
		word=21, parenO, parenC, Semicolon, Comma, INT, CHAR, BLOCKO, BLOCKC, IF, THEN, ELSE, WHILE, RETURN, ASSIGN, INEQUAL, EQUAL, ADD, MUL, NUM,	$, EPSILON
	};
}

class Parser
{
public:
	Parser();
	bool Parsing(Lexer &lexer); // Parsing ����
	void travel(Parse_Node* current);	// Parse Tree �׽�Ʈ��
	Parse_Node* get_Root(); //ParseTree Root ��ȯ

private:
	Parse_Node* New_Node(bool is_Terminal, int type, const std::string & data); // ��� ����
	void Add_child(Parse_Node* current_node, Parse_Node* child); // Child Node �߰�
	void Add_sibling(Parse_Node* current_node, Parse_Node* sibling); // Sibling Node �߰�
	void make_ParseTable(); // ParseTable ����
	void pushT(int l, int c, int n, ...); // ParseTable Stack�� Transition ���
	void set_Index(); // Input Token�� Index ȹ��� Map ����
	void set_NT_data(); // Stack�� data ȹ��� Map ȹ��
	int get_Col(Token token); // Input Token�� ParseTable Index ȹ��

	std::stack<Parse_Node*> stack; // Parser Stack
	Token input_token;
	Parse_Node* Root;	// ParseTree�� Root���
	std::stack<int> ParseTable[21][43];
	std::map<std::string, int> C_index; // Input Token Index Map
	std::map<int, std::string> NT_data; // Stack data Map
};