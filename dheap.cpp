
#include <iostream>
#include <algorithm>
#include <vector>

int div_up(int x, int y)
{
    return x / y + (x % y ? 1 : 0);
}

template <class v, class p>
class Heap
{   
private:
    std::vector<std::pair<v, p>> pairs;
    int d;
public:
    void pushDown(int index = 0) {
        std::pair<v, p> current = pairs[index];

        int firstleafindex = (pairs.size() - 2) / d + 1;
        while (index < firstleafindex) {
            std::pair<std::pair<v, p>, int> tmp = std::make_pair(pairs[d * index + 1], d * index + 1);
            int last_index = (d*(index+1)>pairs.size()-1)?(pairs.size()-1):(d*(index+1));
            for (int i = d * index + 1; i <=last_index; ++i) {
                tmp = ((tmp.first).second < pairs[i].second) ? std::make_pair(pairs[i], i) : tmp;
            }
            if ((tmp.first).second > current.second) {
                pairs[index] = pairs[tmp.second];
                index = tmp.second;
            }
            else {
                break;
            }
        }
        pairs[index] = current;
    }
    Heap<v, p>(std::vector<std::pair<v, p>> list_of_pairs, int vetv = 2) {
        pairs = list_of_pairs;
        d = vetv;
        for (int index = div_up((pairs.size() - 1), d); index >= 0; --index) {
            pushDown(index);
        }
    }
    void bubbleUp(int index = pairs.size() - 1) {
        std::pair<v, p> current = std::make_pair(pairs[index].first, pairs[index].second);
        while (index > 0) {
            int parentIndex = (index - 1) / d;
            if (pairs[parentIndex].second < current.second) {
                pairs[index] = pairs[parentIndex];
                index = parentIndex;
            }
            else {
                break;
            }
        }
        pairs[index] = current;

    }
    
    int get_d() { return d; }
    std::vector<std::pair<v, p>> get_pairs() { return pairs; }

    void insert(v elem, p priority) {
        std::pair<v, p> para = std::make_pair(elem, priority);
        pairs.push_back(para);
        bubbleUp(pairs.size() - 1);
    }
    v top() {
        if (pairs.size() == 0) { return NULL; }
        std::pair<v, p> para = pairs[pairs.size() - 1];
        pairs.resize(pairs.size() - 1);
        if (pairs.size() == 0) {
            return para.first;
        }
        else {
            std::pair<v, p> tmp = pairs[0];
            pairs[0] = para;
            pushDown(0);
            return tmp.first;
        }
    }
    void update(v oldval, p newprior) {
        int index = 0;
        for (int i = 0; i < pairs.size(); ++i) {
            index = (pairs[i] == oldval) ? i : index;
        }
        if (index >= 0) {
            p oldprior = pairs[index].second;
            pairs[index] = std::make_pair(oldval, newprior);
            if (newprior < oldprior) {
                bubbleUp(index);
            }
            else {
                if (newprior > oldprior) {
                    pushDown(index);
                }
            }
        }
    }

};

int main()
{
    auto a = std::make_pair("alloc of memory", 9);

    std::vector<std::pair<std::string, int>> vec = { a , std::make_pair("encrypt password",10), std::make_pair("user interface not work in X brauser",9) };
    Heap<std::string, int> test(vec);
    std::vector<std::pair<std::string, int>> tmp = test.get_pairs();
    for (auto i : tmp) {
        std::cout << i.first << " " << i.second << "\n";
    }
    std::cout << "---------" << "\n";
    std::cout << (test.top())<<"\n";
    std::cout << "---------" << "\n";
    test.insert("test insert", 11);
    std::vector<std::pair<std::string, int>> tmp2 = test.get_pairs();
    for (auto i : tmp2) {
        std::cout << i.first << " " << i.second << "\n";
    }
    std::cout << "---------" << "\n";
    std::cout << test.top() << "\n";
}

