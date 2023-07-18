#pragma once

#ifdef __cplusplus
    #define EXPORT_C extern "C"
    #include <iostream>
#elif
    #define EXPORT_C
#endif




template <typename T>
struct cir_list_node
{
    T *data;
    cir_list_node *next, *prev;

    ~cir_list_node()
    {
        delete data;
    }
};

template <typename T>
struct cir_list
{
public:
    using node = cir_list_node<T>;
    using node_ptr = node*;

private:
    node_ptr head;
    size_t n;

public:
    cir_list() : n(0)
    {
        head = new node{NULL, NULL, NULL}; // Dummy node – having NULL data
        head->next = head;
        head->prev = head;
    }

    size_t size() const
    {
        return n;
    }

    void insert(const T &value)
    {
        node_ptr newNode = new node{new T(value), NULL, NULL};
        n++;
        auto dummy = head->prev;
        dummy->next = newNode;
        newNode->prev = dummy;
        if (head == dummy)
        {
            dummy->prev = newNode;
            newNode->next = dummy;
            head = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void erase(const T &value)
    {
        auto cur = head, dummy = head->prev;
        while (cur != dummy)
        {
            if (*(cur->data) == value)
            {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                if (cur == head)
                    head = head->next;
                delete cur;
                n--;
                return;
            }
            cur = cur->next;
        }
    }

    struct cir_list_it
    {
    private:
        node_ptr ptr;

    public:
        cir_list_it(node_ptr p) : ptr(p)
        {
        }

        T &operator*()
        {
            return *(ptr->data);
        }

        node_ptr get()
        {
            return ptr;
        }

        cir_list_it &operator++()
        {
            ptr = ptr->next;
            return *this;
        }

        cir_list_it operator++(int)
        {
            cir_list_it it = *this;
            ++(*this);
            return it;
        }

        cir_list_it &operator--()
        {
            ptr = ptr->prev;
            return *this;
        }

        cir_list_it operator--(int)
        {
            cir_list_it it = *this;
            --(*this);
            return it;
        }

        friend bool operator==(const cir_list_it &it1, const cir_list_it &it2)
        {
            return it1.ptr == it2.ptr;
        }

        friend bool operator!=(const cir_list_it &it1, const cir_list_it &it2)
        {
            return it1.ptr != it2.ptr;
        }
    };

    cir_list_it begin()
    {
        return cir_list_it{head};
    }

    cir_list_it begin() const
    {
        return cir_list_it{head};
    }

    cir_list_it end()
    {
        return cir_list_it{head->prev};
    }

    cir_list_it end() const
    {
        return cir_list_it{head->prev};
    }

    cir_list(const cir_list<T> &other) : cir_list()
    {
        // Although, the following will insert the elements in reverse order, it won’t matter in logical sense since this is a circular list.
        for (const auto &i : other)
            insert(i);
    }

    cir_list(const std::initializer_list<T> &il) : head(NULL), n(0)
    {
        // Although, the following will insert the elements in reverse order, it won’t matter in logical sense since this is a circular list.
        for (const auto &i : il)
            insert(i);
    }

    ~cir_list()
    {
        while (size())
        {
            erase(*(head->data));
        }
    }
};

struct playlist
{
    cir_list<int> list;

    void insert(int song)
    {
        list.insert(song);
    }

    void erase(int song)
    {
        list.erase(song);
    }

    void loopOnce()
    {
        for (auto &song : list)
            std::cout << song << " ";
        std::cout << std::endl;
    }
};


#define EC_playlist void*

EXPORT_C EC_playlist playlist_new();
EXPORT_C void playlist_insert(EC_playlist, int);
EXPORT_C void playlist_erase(EC_playlist, int);
EXPORT_C void playlist_loopOnce(EC_playlist);
EXPORT_C void playlist_drop(EC_playlist);


EXPORT_C EC_playlist playlist_new() {
    return new playlist{};
}

EXPORT_C void playlist_insert(EC_playlist self, int song) {
    auto ptr = reinterpret_cast<playlist*>(self);
    ptr->insert(song);
}

EXPORT_C void playlist_erase(EC_playlist self, int song) {
    auto ptr = reinterpret_cast<playlist*>(self);
    ptr->erase(song);
}

EXPORT_C void playlist_loopOnce(EC_playlist self) {
    auto ptr = reinterpret_cast<playlist*>(self);
    ptr->loopOnce();
}

EXPORT_C void playlist_drop(EC_playlist self) {
    delete reinterpret_cast<playlist*>(self);
}

EXPORT_C void play();
