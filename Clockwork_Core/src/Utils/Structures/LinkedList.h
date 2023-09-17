#pragma once
#include <iostream>
#include <string>
#include <sstream>//std::stringstream
#include <vector>
//doppelt verkettete liste, wie std::list ähnlich zu der arrayliste vector, die nicht verkettet ist | arbeitet mit kopien der objekte, die eingefügt werden, aber gibt referenzen zu ihnen aus
template<typename type>
struct LinkedList
{

private:
	struct Node//node private, damit man nur in der liste drauf zugreifen kann 
	{

	public:
		type data;//objekt vom datentyp
		Node* next;//pointer auf nächste und vorherige node in der liste
		Node* prev;

	public:
		Node(const type& data) noexcept
			:data(data), prev(nullptr), next(nullptr)
		{}
		Node(type&& data) noexcept
			:data(data), prev(nullptr), next(nullptr)
		{}
		~Node() noexcept
		{}

	};

private:
	unsigned int m_count{ 0 };
	Node* m_first{ nullptr };
	Node* m_last{ nullptr };

public:
	//standardkonstruktor
	LinkedList() noexcept = default;
	//kopierkonstruktor
	LinkedList(const LinkedList<type>& other) noexcept
	{
		Node* temp = other.m_first;//temp geht die andere liste durch und fängt auf first an 
		while (temp)//nur während temp auf ein objekt zeigt 
		{
			addLast(temp->data);//das objekt/element der node in diese liste hinzugefügt
			temp = temp->next;//temp eins weiter nach hinten verschoben
		}

	}
	//movekonstruktor
	LinkedList(LinkedList<type>&& other) noexcept
		:m_count(other.m_count), m_first(other.m_first), m_last(other.m_last)//pointer/member übernehmen
	{
		other.m_first = nullptr;//die pointer der anderen liste auf nullptr setzten, damit die andere liste nicht auf diese elementkette zugreifen kann, sondern nur noch diese hier
		other.m_last = nullptr;//WICHTIG, NIE ALLES LÖSCHEN, da die pointer auf die objekte in diese liste übernommen wurde, also nur der anfangs und endpunkt kopiert wurden 
		other.m_count = 0;//und größe der anderen liste auf 0 setzten
	}
	//expliziter umwandlungskonstruktor von vektor zu liste
	explicit LinkedList(const std::vector<type>& other) noexcept
	{
		for (unsigned int i = 0; i < other.size(); ++i)
		{
			addLast(other.at(i));
		}
	}
	//expliziter umwandlungskonstruktor von array zu liste
	template<unsigned int s>
	explicit LinkedList(const type (&arr)[s]) noexcept
	{
		for (unsigned int i = 0; i < s; ++i)
		{
			addLast(arr[i]);
		}
	}
	//destruktor
	~LinkedList() noexcept
	{
		removeAll();
	}

public:
	//element am ende der liste hinzufügen
	void addLast(const type& data) noexcept
	{
		Node* node = new Node(data);
		if (m_count == 0)
		{
			m_last = node;//wenn liste leer war ist, zeigt first und last auf das einzige element 
			m_first = node;
		}
		else
		{
			m_last->next = node;//sonst zeigt next vom letzten element der liste auf das neue element
			node->prev = m_last;//und prev vom neuen element zeigt auf das letzte element der liste
			m_last = node;//dann zeigt last auf das neue element und somit wurde das neue element an die liste drangehangen
		}
		m_count++;
	}
	//element am ende der liste hinzufügen
	void addLast(type&& data) noexcept
	{
		Node* node = new Node(std::move(data));
		if (m_count == 0)
		{
			m_last = node;//wenn liste leer war ist, zeigt first und last auf das einzige element 
			m_first = node;
		}
		else
		{
			m_last->next = node;//sonst zeigt next vom letzten element der liste auf das neue element
			node->prev = m_last;//und prev vom neuen element zeigt auf das letzte element der liste
			m_last = node;//dann zeigt last auf das neue element und somit wurde das neue element an die liste drangehangen
		}
		m_count++;
	}
	//element am anfang der liste hinzufügen
	void addFirst(const type& data) noexcept
	{
		Node* node = new Node(data);
		if (m_count == 0)
		{
			m_last = node;//wenn liste leer war ist, zeigt first und last auf das einzige element 
			m_first = node;
		}
		else
		{
			m_first->prev = node;//sonst zeigt prev vom ersten element der liste auf das neue element
			node->next = m_first;//und next vom neuen element zeigt auf das erste element der liste
			m_first = node;//dann zeigt first auf das neue element und somit wurde das neue element an den anfang der liste gesetzt
		}
		m_count++;
	}
	//element am anfang der liste hinzufügen
	void addFirst(type&& data) noexcept
	{
		Node* node = new Node(std::move(data));
		if (m_count == 0)
		{
			m_last = node;//wenn liste leer war ist, zeigt first und last auf das einzige element 
			m_first = node;
		}
		else
		{
			m_first->prev = node;//sonst zeigt prev vom ersten element der liste auf das neue element
			node->next = m_first;//und next vom neuen element zeigt auf das erste element der liste
			m_first = node;//dann zeigt first auf das neue element und somit wurde das neue element an den anfang der liste gesetzt
		}
		m_count++;
	}
	//fügt das element an der position in der liste und verschiebt den rest der liste nach hinten(einschließlich dem element, dass vorher auf der position war) 
	void add(const type& data, unsigned int pos) noexcept
	{
		if (m_count == 0)
		{
			Node* node = new Node(data);
			m_last = node;//wenn liste leer war ist, zeigt first und last auf das einzige element 
			m_first = node;
			m_count++;
		}
		else if (pos == 0) addFirst(data);
		else if (pos >= m_count)addLast(data);//wenn eine zu hohe zahl eingegeben wird, soll nicht das letzte element in der liste verschoben werden, sondern eins an die liste dran gehangen werden
		else
		{
			Node* node = new Node(data);
			Node* temp;
			if (pos < m_count - pos)
			{
				temp = m_first;
				for (unsigned int i = 0; i < pos; i++)
				{
					temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
				}
			}
			else
			{
				temp = m_last;
				for (unsigned int i = m_count - 1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
				{
					temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
				}
			}
			temp->prev->next = node;//neues element mit dem element vor der position verketten
			node->prev = temp->prev;
			temp->prev = node;//element an der position des neuen elements eins nach hinten schieben und dies mit dem neuen element verketten 
			node->next = temp;
			m_count++;
		}
	}
	//fügt das element an der position in der liste und verschiebt den rest der liste nach hinten(einschließlich dem element, dass vorher auf der position war) 
	void add(type&& data, unsigned int pos) noexcept
	{
		if (m_count == 0)
		{
			Node* node = new Node(std::move(data));
			m_last = node;//wenn liste leer war ist, zeigt first und last auf das einzige element 
			m_first = node;
			m_count++;
		}
		else if (pos == 0) addFirst(std::move(data));
		else if (pos >= m_count)addLast(std::move(data));//wenn eine zu hohe zahl eingegeben wird, soll nicht das letzte element in der liste verschoben werden, sondern eins an die liste dran gehangen werden
		else
		{
			Node* node = new Node(std::move(data));
			Node* temp;
			if (pos < m_count - pos)
			{
				temp = m_first;
				for (unsigned int i = 0; i < pos; i++)
				{
					temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
				}
			}
			else
			{
				temp = m_last;
				for (unsigned int i = m_count - 1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
				{
					temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
				}
			}
			temp->prev->next = node;//neues element mit dem element vor der position verketten
			node->prev = temp->prev;
			temp->prev = node;//element an der position des neuen elements eins nach hinten schieben und dies mit dem neuen element verketten 
			node->next = temp;
			m_count++;
		}
	}
	//erstes element ausgeben
	type& getFirst() noexcept
	{
		return m_first->data;
	}
	//letztes element ausgeben
	type& getLast() noexcept
	{
		return m_last->data;
	}
	//element an einer stelle in der liste suchen, zugriff wie bei array 0 bis size-1
	type& get(unsigned int pos) noexcept
	{
		Node* temp;
		if (pos < m_count - pos)
		{
			temp = m_first;
			for (unsigned int i = 0; i < pos; i++)
			{
				temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
			}
		}
		else
		{
			temp = m_last;
			for (unsigned int i = m_count -1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
			{
				temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
			}
		}
		return temp->data;
	}
	//erstes element ausgeben
	const type& getFirst() const noexcept
	{
		return m_first->data;
	}
	//letztes element ausgeben
	const type& getLast() const noexcept
	{
		return m_last->data;
	}
	//element an einer stelle in der liste suchen, zugriff wie bei array 0 bis size-1
	const type& get(unsigned int pos) const noexcept
	{
		Node* temp;
		if (pos < m_count - pos)
		{
			temp = m_first;
			for (unsigned int i = 0; i < pos; i++)
			{
				temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
			}
		}
		else
		{
			temp = m_last;
			for (unsigned int i = m_count - 1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
			{
				temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
			}
		}
		return temp->data;
	}
	//ersetzt das erste element
	void setFirst(const type& data) noexcept
	{
		m_first->data = data;
	}
	//ersetzt das erste element
	void setFirst(type&& data) noexcept
	{
		m_first->data = std::move(data);
	}
	//ersetzt das letzte element
	void setLast(const type& data) noexcept
	{
		m_last->data = data;
	}
	//ersetzt das letzte element
	void setLast(type&& data) noexcept
	{
		m_last->data = std::move(data);
	}
	//ersetzt das element an der position durch ein neues
	void set(const type& data, unsigned int pos) noexcept
	{
		if (m_count == 1 || pos == 0) m_first->data = data;
		else if (pos >= m_count - 1)m_last->data = data;
		else
		{
			Node* temp;
			if (pos < m_count - pos)
			{
				temp = m_first;
				for (unsigned int i = 0; i < pos; i++)
				{
					temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
				}
			}
			else
			{
				temp = m_last;
				for (unsigned int i = m_count - 1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
				{
					temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
				}
			}
			temp->data = data;
		}
	}
	//ersetzt das element an der position durch ein neues
	void set(type&& data, unsigned int pos) noexcept
	{
		if (m_count == 1 || pos == 0) m_first->data = std::move(data);
		else if (pos >= m_count - 1)m_last->data = std::move(data);
		else
		{
			Node* temp;
			if (pos < m_count - pos)
			{
				temp = m_first;
				for (unsigned int i = 0; i < pos; i++)
				{
					temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
				}
			}
			else
			{
				temp = m_last;
				for (unsigned int i = m_count - 1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
				{
					temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
				}
			}
			temp->data = std::move(data);
		}
	}
	//gleiches element in der liste suchen und eine referenz dazu ausgeben, sonst NULL
	type& take(const type& object) noexcept
	{
		Node* temp = m_first;
		while (temp!=m_last)//temp startet auf dem ersten element und geht bis zum vorletzten
		{
			if (temp->data == object)//wenn das objekt von temp das gesuchte ist, wird die methode abgebrochen und das objekt von temp wird ausgegeben
				return temp->data;
			else
				temp = temp->next;//sonst wird temp um eins verschoben
		}
		if (temp->data == object)
			return temp->data;//das letzte element wird auch noch überprüft
		else
			return NULL;//sonst wird null ausgegeben
	}
	//boolean, ob die liste ein gleiches element enthält
	bool contains(const type& object) noexcept
	{
		Node* temp = m_first;
		while (temp != m_last)//temp startet auf dem ersten element und geht bis zum vorletzten
		{
			if (temp->data == object)//wenn das objekt gefunden wurde, wird true ausgegeben und die methode abgebrochen
				return true;
			else
				temp = temp->next;//sonst wird temp um eins verschoben
		}
		if (temp->data == object)
			return true;//das letzte element wird auch noch überprüft
		else
			return false;//sonst wird false ausgegeben
	}
	//erstes element entfernen
	void removeFirst() noexcept
	{
		if (m_first == m_last)//wenn nur ein element in liste ist, spezialfall
		{
			delete m_first;
			m_last = nullptr;
			m_count--;
		}
		else
		{
			Node* temp = m_first;
			m_first->next->prev = nullptr;
			m_first = m_first->next;
			delete temp;
			m_count--;
		}
	}
	//letztes element entfernen
	void removeLast() noexcept
	{
		if (m_first == m_last)//wenn nur ein element in liste ist, spezialfall
		{
			delete m_last;
			m_first = nullptr;
			m_count--;
		}
		else
		{
			Node* temp = m_last;
			m_last->prev->next = nullptr;
			m_last = m_last->prev;
			delete temp;
			m_count--;
		}
	}
	//alle elemente entfernen
	void removeAll() noexcept
	{
		Node* temp = m_first;
		while (temp!=m_last)
		{
			temp = temp->next;
			delete temp->prev;
			m_count--;
		}
		delete m_last;
		m_count--;
		m_first = nullptr;
		m_last = nullptr;
	}
	//element an der position entfernen
	void remove(unsigned int pos) noexcept//element an einer stelle in der liste löschen
	{
		if (pos==0)
		{
			removeFirst();
		}
		else if (pos == m_count - 1)//count-1, da es auf letztes element überprüft wird und nicht die size 
		{
			removeLast();
		}
		else
		{
			Node* temp;
		if (pos < m_count - pos)
		{
			temp = m_first;
			for (unsigned int i = 0; i < pos; i++)
			{
				temp = temp->next;//liste wird von vorne bis zum gesuchten element durchgegangen
			}
		}
		else
		{
			temp = m_last;
			for (unsigned int i = m_count - 1; i > pos; i--)//count-1, da hier mit den elementen gerechnet wird und nicht mit der size, also letzte element ist auf size-1 | vorher die schleife geht auch vom 0. element bis zur pos, also muss hier vom letzten element(size-1) bis zur pos
			{
				temp = temp->prev;//liste wird von hinten bis zum gesuchten element durchgegangen
			}
		}
		temp->prev->next = temp->next;//next von dem element vor dem gelöschten zeigt auf das element nach dem gelöschten
		temp->next->prev = temp->prev;//prev von dem element nach dem gelöschten zeigt auf das element vor dem gelöschten
		delete temp;//zum schluss wird die node gelöscht, da sie dynamisch erstellt wurde 
		m_count--;
		}
	}
	//spezifisches element aus der liste entfernen mit boolean, ob es entfernt wurde
	bool removeO(const type& object) noexcept
	{
		if (m_first == nullptr)
			return false;
		if (m_first->data == object)//das erste und das letzte objekt müssen seperat überprüft werden, da sie jeweils an einer stelle keinen nachfolger/vorgänger haben
		{
			removeFirst();
			return true;
		}
		else if (m_last->data == object)
		{
			removeLast();
			return true;
		}
		Node* temp = m_first->next;
		while (temp != m_last)//temp startet auf dem ersten element und geht bis zum vorletzten
		{
			if (temp->data == object)//wenn die node gefunden wurde, in der das objekt enthalten ist, wird sie gelöscht
			{
				temp->prev->next = temp->next;//next von dem element vor dem gelöschten zeigt auf das element nach dem gelöschten
				temp->next->prev = temp->prev;//prev von dem element nach dem gelöschten zeigt auf das element vor dem gelöschten
				delete temp;//zum schluss wird die node gelöscht, da sie dynamisch erstellt wurde 
				m_count--;
				return true;
			}
			else
				temp = temp->next;//sonst wird temp um eins verschoben
		}
		return false;//sonst wird false ausgegeben
	}
	//gibt die node an der position aus
	Node* getNode(unsigned int pos) const noexcept
	{
		Node* temp;
		if (pos < m_count - pos)
		{
			temp = m_first;
			for (unsigned int i = 0; i < pos; i++)
			{
				temp = temp->next;
			}
		}
		else
		{
			temp = m_last;
			for (unsigned int i = m_count - 1; i > pos; i--)
			{
				temp = temp->prev;
			}
		}
		return temp;
	}
	//verschiebt node dest zu src, wobei src dann um eins nach rechts verschoben wird 
	inline void insertNode(Node* src, Node* dest) noexcept
	{
		if (src->prev == nullptr)
			m_first = src->next;
		else
			src->prev->next = src->next;
		if (src->next == nullptr)
			m_last = src->prev;
		else
			src->next->prev = src->prev;

		src->prev = dest->prev;
		if (dest->prev == nullptr)
			m_first = src;
		else
			dest->prev->next = src;

		src->next = dest;
		dest->prev = src;
	}
	//vertauscht 2 nodes
	inline void swapNodes(Node* n1, Node* n2) noexcept
	{
		if (n1->next == n2)
		{
			Node* prev = n1->prev;
			n1->prev = n2;
			n1->next = n2->next;
			if (n2->next == nullptr)
				m_last = n1;
			else
				n2->next->prev = n1;
			n2->next = n1;
			n2->prev = prev;
			if (prev == nullptr)
				m_first = n2;
			else
				prev->next = n2;

		}
		else if (n2->next == n1)
		{
			Node* prev = n2->prev;
			n2->prev = n1;
			n2->next = n1->next;
			if (n1->next == nullptr)
				m_last = n2;
			else
				n1->next->prev = n2;
			n1->next = n2;
			n1->prev = prev;
			if (prev == nullptr)
				m_first = n1;
			else
				prev->next = n1;
		}
		else
		{
			Node* prev = n1->prev;
			Node* next = n1->next;

			n1->prev = n2->prev;
			n1->next = n2->next;

			n2->prev = prev;
			n2->next = next;

			if (n1->prev == nullptr)
				m_first = n1;
			else
				n1->prev->next = n1;
			if (n1->next == nullptr)
				m_last = n1;
			else
				n1->next->prev = n1;

			if (n2->prev == nullptr)
				m_first = n2;
			else
				n2->prev->next = n2;
			if (n2->next == nullptr)
				m_last = n2;
			else
				n2->next->prev = n2;
		}
	}

public:
	//alle elemente einer liste in diese liste kopieren
	LinkedList<type>& operator=(const LinkedList<type>& other) noexcept
	{
		removeAll();//erstmal alle listenelemente löschen 
		Node* temp = other.m_first;//temp geht die andere liste durch und fängt auf first an 
		while (temp)//nur während temp auf ein objekt zeigt
		{
			addLast(temp->data);//das objekt/element der node in diese liste hinzugefügt
			temp = temp->next;//temp eins weiter nach hinten verschoben
		}
		return *this;//dieses objekt ausgegeben
	}
	//alle elemente einer liste in diese liste verschieben, dabei wird die andere liste leer | viel effizienter, als copy, wird mit ob1 = std::move(ob1); aufgerufen
	LinkedList<type>& operator=(LinkedList<type>&& other) noexcept
	{
		removeAll();//erstmal diese liste leer machen
		m_first = other.m_first;//first und last pointer zu den elementen der anderen liste kopieren
		m_last = other.m_last;
		m_count = other.m_count;//anzahl/size kopieren
		other.m_first = nullptr;//die pointer der anderen liste auf nullptr setzten, damit die andere liste nicht auf diese elementkette zugreifen kann, sondern nur noch diese hier
		other.m_last = nullptr;//WICHTIG, NIE ALLES LÖSCHEN, da die pointer auf die objekte in diese liste übernommen wurde, also nur der anfangs und endpunkt kopiert wurden 
		other.m_count = 0;//und größe der anderen liste auf 0 setzten
		return *this;
	}
	//liste als stream ausgeben | "LinkedList start:element1|element2|element3:LinkedList stop"
	friend std::ostream& operator<<(std::ostream& stream, const LinkedList<type>& list) noexcept
	{
		stream << "LinkedList start:";
		if (list.m_count > 0)
		{
			Node* temp = list.m_first;
			while (temp != list.m_last)
			{
				stream << temp->data;
				stream << "|";
				temp = temp->next;
			}
			stream << list.m_last->data;
		}
		stream << ":LinkedList stop";
		return stream;
	}
	//same as addLast
	LinkedList<type>& operator+=(const type& other) noexcept
	{
		addLast(other);//ruft immer addLast(type&) auf, da die referenz immer lvalue variable/objekt ist
		return *this;
	}
	//same as addLast
	LinkedList<type>& operator+=(type&& other) noexcept
	{
		addLast(std::move(other));//ruft immer addLast(type&) auf, da die referenz immer lvalue variable/objekt ist, deswegen muss es mit std::move() zu rvalue referenz umgewandelt werden
		return *this;
	}
	//same as get
	type& operator[](unsigned int pos) noexcept
	{
		return get(pos);
	}
	//same as get
	const type& operator[](unsigned int pos) const noexcept
	{
		return get(pos);
	}
	//expliziter umwandlungsoperator von liste zu vektor
	explicit operator std::vector<type>() const noexcept
	{
		std::vector<type> temp;
		temp.reserve(m_count);
		for (unsigned int i = 0; i < m_count; ++i)
		{
			temp.push_back(get(i));
		}
		return temp;
	}
	//liste aus stream entnehmen | "LinkedList start:element1|element2|element3:LinkedList stop"
/*	friend std::istream& operator>>(std::istream& stream, LinkedList<type>& list)
	{
		std::stringstream ss;
		ss << stream.rdbuf();
		std::string temp = ss.str();
		std::size_t pos = temp.find("LinkedList start:");
		if (pos!=std::string::npos)
		{
			std::size_t count{ 0 };
			for (size_t i = pos + 17; i < temp.find(":LinkedList stop");)
			{
				size_t size = temp.find("|", i) - i;
				std::stringstream add;
				add << temp.substr(i, size);
				type t; 
				add >> t;
				if (list.size() <= count)
					list.addLast(t);
				else
				{
					list.set(t, count);
				}

				i += size + 1;
				++count;
			}
		}
		stream.clear();
		return stream;
	}*/

public:
	//größe der liste 
	const unsigned int size() const noexcept
	{
		return m_count;
	}
	//liste ist leer, wenn keine elemente in ihr gespeichert sind 
	const bool empty() const noexcept
	{
		return m_count == 0;
	}
	//liste als string ausgeben | "LinkedList start:element1|element2|element3:LinkedList stop"
	const std::string toString() const noexcept
	{
		std::stringstream stream;
		stream << "LinkedList start:";
		if (m_count > 0)
		{
			Node* temp = m_first;
			while (temp != m_last)
			{
				stream << temp->data;//<< verarbeitet alle typen zu einem stringstream, anstatt += zu benutzen | wandelt auch zahlen richtig in chars um 
				stream << "|";
				temp = temp->next;
			}
			stream << m_last->data;
			stream << "|";
		}
		stream << ":LinkedList stop";
		return stream.str();//stringstream in string umwandeln
	}

	private:
		inline void insertNodeFast(Node* src, Node* dest) noexcept
		{
			src->prev->next = src->next;
			if (src->next == nullptr)
				m_last = src->prev;
			else
				src->next->prev = src->prev;

			src->prev = dest->prev;
			if (dest->prev == nullptr)
				m_first = src;
			else
				dest->prev->next = src;

			src->next = dest;
			dest->prev = src;
		}
		inline const type& findPivot(const type& x, const type& y, const type& z, bool(*compare)(const type&, const type&)) noexcept
		{//!compare(t1,t2) == t1>=t2
			if ( (!compare(y, x)) && (!compare(z, y)) )
				return y;
			if ((!compare(y, z)) && (!compare(x, y)))
				return y;

			if ( (!compare(z, x)) && (!compare(y, z)) )
				return z;
			if ((!compare(z, y)) && (!compare(x, z)))
				return z;

			if ( (!compare(x, y)) && (!compare(z, x)) )
				return x;
			if ((!compare(x, z)) && (!compare(y, x)))
				return x;

		}
		inline void merge(unsigned int min, unsigned int middle, unsigned int max, bool(*compare)(const type&, const type&)) noexcept
		{
			unsigned int insertpos = min;
			unsigned int shift = 0;
			unsigned int rightptr = middle + 1;
			while (insertpos <= middle + shift && rightptr <= max)
			{
				if (compare(get(rightptr), get(insertpos)))
				{
					insertNodeFast(getNode(rightptr), getNode(insertpos));
					++rightptr;
					++shift;
				}
				++insertpos;
			}
		}
		inline void mergesort(unsigned int left, unsigned int right, bool(*compare)(const type&, const type&)) noexcept
		{
			if (left < right)
			{
				unsigned int middle = (left + right) / 2;
				mergesort(left, middle, compare);
				mergesort(middle + 1, right, compare);
				merge(left, middle, right, compare);
			}
		}
		inline void quicksort(int min, int max, bool(*compare)(const type&, const type&)) noexcept
		{
			int left = min;
			int right = max;
			const type pivot = findPivot(get(min), get((min + max) / 2), get(max), compare);
			do 
			{
				while (compare(get(left), pivot))
					++left;
				while (compare(pivot, get(right)))
					--right;
				if (left < right)
				{
					type temp(std::move(get(left)));
					get(left) = std::move(get(right));
					get(right) = std::move(temp);
				}
				if (left <= right)
				{
					++left;
					--right;
				}
			} while (left<=right);
			if (min < right)
				quicksort(min, right, compare);
			if (left < max)
				quicksort(left, max, compare);
		}

	public:
		//t1<=t2
		inline static bool compareAscendingMerge(const type& t1, const type& t2) noexcept
		{
			return t1 <= t2;
		}
		//t1>=t2
		inline static bool compareDescendingMerge(const type& t1, const type& t2) noexcept
		{
			return t1 >= t2;
		}
		//t1<t2
		inline static bool compareAscendingQuick(const type& t1, const type& t2) noexcept
		{
			return t1 < t2;
		}
		//t1>t2
		inline static bool compareDescendingQuick(const type& t1, const type& t2) noexcept
		{
			return t1 > t2;
		}
		/*sorts the list using mergesort and swapping pointer from the nodes | this method is reliable with the speed, but not so fast 
		the default compare function is compareAscendingMerge: type1<=type2<=type3, but the functionpointer parameter can be set to LinkedList<type>::compareDescendingMerge type1>=type2>=type3, 
		or a custom compare function between the 2 types bool compare(const type&, const type&); the function should compare with <=, or >=
			*/
		void sortListBig(bool(*compare)(const type&, const type&) = &compareAscendingMerge) noexcept
		{
			mergesort(0, m_count - 1, compare);
		}
		/*sorts the list using quicksort and swapping the types | this method is fast, but not so reliable with the speed
		the default compare function is compareAscendingQuick type1<type2<type3, but the functionpointer parameter can be set to LinkedList<type>::compareDescendingQuick type1>type2>type3, 
		or a custom compare function between the 2 types bool compare(const type&, const type&);  the function should compare with <, or >
		*/
		void sortListSmall(bool(*compare)(const type&, const type&) = &compareAscendingQuick) noexcept
		{
			quicksort(0, m_count - 1, compare);
		}

};