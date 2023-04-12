#pragma once

#include <string>

class Entry
{
protected:
    Entry();

public:
    // virtual void Operation() = 0; // error
    virtual ~Entry() {}
    virtual std::string getName() const = 0;
    virtual int getSize() const = 0;
    virtual void addEntry(Entry *entry) {}
    virtual void printList(const std::string &str) = 0;

    void printList()
    {
        printList("");
    }
    std::string toString() const
    {
        return getName() + " (" + std::to_string(getSize()) + ")";
    }
};

#include <iostream>
#include <vector>

class Directory : public Entry
{
public:
    Directory(const std::string &name) : m_name(name) {}
    ~Directory()
    {
        for (auto it : m_dirs)
        {
            delete it;
        }
        m_dirs.clear();
    }
    virtual std::string getName() const override
    {
        return m_name;
    }
    virtual int getSize() const
    {
        int size = 0;
        for (auto it : m_dirs)
        {
            size += it->getSize();
        }
        return size;
    }
    virtual void addEntry(Entry *entry) override
    {
        m_dirs.push_back(entry);
    }
    virtual void printList(const std::string &str) override
    {
        std::cout << str << "/" << toString() << std::endl;
        for (auto it : m_dirs)
        {
            it->printList(str + "/" + m_name);
        }
    }

private:
    std::string m_name;
    std::vector<Entry *> m_dirs;
};

class File : public Entry
{
public:
    File(const std::string &name, int size) : m_name(name), m_size(size) {}
    virtual std::string getName() const override
    {
        return m_name;
    }
    virtual int getSize() const override
    {
        return m_size;
    }

    virtual void printList(const std::string &str) override
    {
        std::cout << str << "/" << toString() << std::endl;
    }

private:
    std::string m_name;
    int m_size;
};

int main()
{
    Directory *root = new Directory("root");
    Directory *bin = new Directory("bin");
    Directory *tmp = new Directory("tmp");
    Directory *usr = new Directory("usr");

    root->addEntry(bin);
    root->addEntry(tmp);
    root->addEntry(usr);
    bin->addEntry(new File("vi", 3000));
    bin->addEntry(new File("latex", 2000));
    static_cast<Entry *>(root)->printList();

    Directory *yuki = new Directory("yuki");
    Directory *hanako = new Directory("hanako");
    Directory *tomura = new Directory("tomura");

    usr->addEntry(yuki);
    usr->addEntry(hanako);
    usr->addEntry(tomura);
    yuki->addEntry(new File("diary.html", 100));
    hanako->addEntry(new File("memo.tex", 1024));
    tomura->addEntry(new File("junk.mail", 40));

    static_cast<Entry *>(root)->printList();

    // for test coverage
    {
        File *f = new File("123.txt", 1);
        f->addEntry(root);
        f->printList("");
        delete f;
    }
    {
        yuki->printList("");
    }
    {
        File *f = new File("123.txt", 1);
        Entry *e = new Directory("test");
        e->addEntry(f);
        e->printList("");
        e->toString();
        delete e;
    }
    delete root;
    return 0;
}