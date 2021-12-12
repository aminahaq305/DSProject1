#include "sequence.h"

Sequence::Sequence(size_type sz)
{
	head = nullptr;
	tail = nullptr;
	numElts = 0;
	if (sz > 0) {
		numElts = sz;
		for (unsigned int i = 0; i < sz; i++) {
			SequenceNode* newNode;
			newNode = new SequenceNode(-1);
			if (head == nullptr) {
				head = newNode;
				tail = newNode;
			}
			else {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
		}
	}
}

Sequence::Sequence(const Sequence& s)
{
	numElts = s.numElts;
	SequenceNode* current = s.head;
	if (s.numElts >= 1) {
		SequenceNode* newNode;
		newNode = new SequenceNode(current->elt);
		head = newNode;
		tail = newNode;
		current = current->next;
		while (current != nullptr) {
			SequenceNode* newNode;
			newNode = new SequenceNode(current->elt);
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
			current = current->next;
		}
	}
	else {
		head = nullptr;
		tail = nullptr;
	}
}


Sequence::~Sequence()
{
	SequenceNode* killMe;
	SequenceNode* killMeNext;
	killMe = head;
	while (killMe != nullptr) {
		killMeNext = killMe->next;
		delete killMe;
		killMe = killMeNext;
	}
}

Sequence& Sequence::operator=(const Sequence& s)
{
	this->~Sequence();
	head = nullptr;
	tail = nullptr;
	numElts = s.numElts;
	SequenceNode* current = s.head;
	SequenceNode* newNode;
	newNode = new SequenceNode(current->elt);
	head = newNode;
	tail = newNode;
	current = current->next;
	while (current != nullptr) {
		SequenceNode* newNode;
		newNode = new SequenceNode(current->elt);
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		current = current->next;
	}
	return (*this);
}

Sequence::value_type& Sequence::operator[](size_type position)
{
	SequenceNode* current = head;
	if (position < 0 || position > numElts - 1) {
		throw exception("Position out of bounds");
	}
	else if (position == 0) {
		return head->elt;
	}
	else {
		for (unsigned int i = 0; i < position; i++) {
			current = current->next;
		}
		return current->elt;
	}
}

void Sequence::push_back(const value_type& value)
{
	numElts++;
	SequenceNode* newNode;
	newNode = new SequenceNode(value);
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

void Sequence::pop_back()
{
	if (tail == nullptr) {
		throw exception("Sequence is empty");
	}
	else {
		SequenceNode* deleteptr = tail;
		if (numElts == 1) {
			head = tail = nullptr;
			delete deleteptr;
		}
		else {
			tail = tail->prev;
			tail->next = nullptr;
			delete deleteptr;
		}
		numElts--;
	}
}

void Sequence::insert(size_type position, value_type value)
{
	SequenceNode* newNode;
	newNode = new SequenceNode(value);
	SequenceNode* current;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else if (position == 0) {
		newNode->next = head;
		head = newNode;
	}
	else if (position >= numElts || position < 0) {
		throw exception("Invalid Index");
	}
	else {
		current = head;
		for (unsigned int i = 0; i < position - 1; i++) {
			current = current->next;
		}
		newNode->prev = current;
		newNode->next = current->next;
		current->next->prev = newNode;
		current->next = newNode;
	}
	numElts++;
}

const Sequence::value_type& Sequence::front() const
{
	if (head == nullptr) {
		throw exception("Sequence is empty");
	}
	else {
		return head->elt;
	}
}

const Sequence::value_type& Sequence::back() const
{
	if (tail == nullptr) {
		throw exception("Sequence is empty");
	}
	else {
		return tail->elt;
	}
}

bool Sequence::empty() const
{
	if (head == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

Sequence::size_type Sequence::size() const
{
	return numElts;
}

void Sequence::clear()
{
	this->~Sequence();
	head = tail = nullptr;
	numElts = 0;
}

void Sequence::erase(size_type position, size_type count)
{
	SequenceNode* deleteptr = head;
	SequenceNode* first = head;
	SequenceNode* last = head;
	if (position != 0 && position + count - 1 < numElts - 1) {
		for (unsigned int i = 0; i < position - 1; i++) {
			first = first->next;
		}
		deleteptr = first->next;
		last = first->next;
		for (unsigned int i = 0; i < count; i++) {
			last = last->next;
			delete deleteptr;
			numElts--;
			deleteptr = last;
		}
		first->next = last;
		last->prev = first;
	}
	else if (position == 0) {
		last = deleteptr = head;
		for (unsigned int i = 0; i < count; i++) {
			first = first->next;
			last = last->next;
			delete deleteptr;
			numElts--;
			deleteptr = first;
		}
		head = first;
		head->prev = nullptr;
	}
	else if (position + count - 1 == numElts - 1) {
		for (unsigned int i = 0; i < position - 1; i++) {
			last = last->next;
		}
		deleteptr = last->next;
		first = last->next;
		while (deleteptr != nullptr) {
			first = first->next;
			delete deleteptr;
			numElts--;
			deleteptr = first;
		}
		tail = last;
		tail->next = nullptr;
	}
	else {
		throw exception("Invalid index");
	}
}
void Sequence::print(ostream& outputStream) const {
	outputStream << "<";
	SequenceNode* current = head;
	while (current != nullptr) {
		outputStream << current->elt;
		if (current->next) {
			outputStream << ", ";
		}
		current = current->next;
	}
	outputStream << ">" << endl;
}

ostream& operator<<(ostream& os, Sequence& s)
{
	s.print(os);
	return os;
}