#include <iostream>
#include <forward_list>
#include <vector>
#include <string>

using namespace std;

template <typename Key, typename Value, typename Hasher = hash<Key>>
class HashTable {
private:
    vector<forward_list<pair<Key, Value>>*> data;
    Hasher hash;
    size_t size_vec;
public:
    HashTable() {
        size_t size = 2;
        data.resize(size);
        for (size_t i = 0; i < size; i++) {
            data[i] = new forward_list<pair<Key, Value>>;
        }
        size_vec = 0;
    }
    HashTable(size_t size) {
        data.resize(size);
        for (size_t i = 0; i < size; i++) {
            data[i] = new forward_list<pair<Key, Value>>;
        }
        size_vec = 0;
    }
    ~HashTable() {
        for (size_t i = 0; i < data.size(); i++) {
            delete data[i];
        }
    }
    size_t Size() {
        return size_vec;
    }
    size_t Capacity() {
        return data.size();
    }
    void Rehash(size_t size) {
        vector<forward_list<pair<Key, Value>>*> new_data;
        new_data.resize(size);
        for (size_t i = 0; i < size; i++) {
            new_data[i] = new forward_list<pair<Key, Value>>;
        }
        for (size_t i = 0; i < data.size(); i++) {
            auto it = data[i]->begin();
            while (it != data[i]->end()) {
                auto h = static_cast<size_t>(hash((*it).first)) % new_data.size();
                new_data[h]->push_front(make_pair((*it).first, (*it).second));
                it++;
            }
        }
        for (size_t i = 0; i < data.size(); i++) {
            delete data[i];
        }
        data.resize(size);
        for (size_t i = 0; i < size; i++) {
            data[i] = new_data[i];
        }
    }
    void Insert(const Key& key, const Value& value) {
        auto h = static_cast<size_t>(hash(key)) % data.size();
        data[h]->push_front(make_pair(key, value));
        size_vec++;
        if (data[h]->max_size() == 5) {
            Rehash(data.size() * 2);
        }
    }
    void Erase(const Key& key) {
        auto h = static_cast<size_t>(hash(key)) % data.size();
        auto it = data[h]->begin();
        while (it != data[h]->end()) {
            if ((*it).first == key) {
                data[h]->remove(*it);
                size_vec--;
                return;
            }
            it++;
        }
        exit(1);
    }
    void Clear() {
        for (size_t i = 0; i < data.size(); i++) {
            delete data[i];
        }
        size_t size = 2;
        data.resize(size);
        for (size_t i = 0; i < size; i++) {
            data[i] = new forward_list<pair<Key, Value>>;
        }
        size_vec = 0;
    }
    bool Contains(Key key) {
        auto h = static_cast<size_t>(hash(key)) % data.size();
        auto it = data[h]->begin();
        while (it != data[h]->end()) {
            if ((*it).first == key) {
                return true;
            }
            it++;
        }
        return false;
    }
    Value operator[](Key key) const {
        auto h = static_cast<size_t>(hash(key)) % data.size();
        if (Contains(key)) {
            for (auto x : *data[h]) {
                if (x.first == key) {
                    return x.second;
                }
            }
        }
        return Value();
    }
    Value& operator[](Key key) {
        auto h = static_cast<size_t>(hash(key)) % data.size();
        if (!Contains(key)) {
            Insert(key, Value());
        }
        auto it = data[h]->begin();
        while (it != data[h]->end()) {
            if ((*it).first == key) {
                return it->second;
            }
            it++;
        }
    }
};
struct hash_function {
    size_t operator()(string val) {
        size_t h = 0;
        for (size_t i; i < val.size(); i++) {
        h = ((h * 17) + val[i] - 48);
        }
        return h;
    }
};

int main()
{
    HashTable<int, int> myTable(3);
    myTable.Insert(1, 5);
    myTable.Insert(235, 5);
    myTable.Insert(87, 5);
    myTable.Insert(34, 5);
    myTable.Insert(91, 5);
    myTable.Insert(21, 5);
    myTable.Insert(478, 5);
    myTable.Insert(1645, 5);
    myTable.Erase(1645);
    myTable.Rehash(20);
    myTable[21] = 7;
    cout << myTable[21] << endl;
    cout << myTable.Size() << endl;
}