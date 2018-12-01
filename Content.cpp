#include <iostream>
#include <vector>
#include <string>
class Content;
class ContentR;

using namespace std;

class Content
{
    string __text;
    int __user_id;
    int __id;
    
    vector <ContentR*> relations;
    static vector <Content*> all_contents;

    public:
    Content(int user_id ,string text);   
    
    int GetUserId();
    void edit_text(string text);
    void add_relation(int related_id, int kind);

    friend ostream& operator <<(ostream& stream ,Content content);
    
    static Content* get_content(int id);

};

enum CRType{
    AnsweredQuestion,
    DuplicatedQuestion
};
class ContentR
    {
        int __next_type;
        int __next;
        
        public:
        
        Content* get_next();
        int      get_next_type();
        ContentR::ContentR(int next, int next_type);
    };


std::ostream& operator <<(std::ostream& stream ,Content content)
    {
        stream << content.__text << std::endl;
    }

int Content::GetUserId()
    {
        return this->__user_id;
    }
void Content::edit_text(std::string text)
    {
        __text = text;
    }
Content::Content(int user_id ,string text)
    {
        __user_id = user_id;
        __text = text;
        __id = all_contents.size()+1;
        all_contents.push_back(this);
    }

Content* Content::get_content(int id)
    {
        return all_contents[id];
    }

Content* ContentR::get_next()
    {
        return Content::get_content(__next);
    }

int ContentR::get_next_type()
    {
        return __next_type;
    }

void Content::add_relation(int related_id, int kind)
    {
        this->relations.emplace_back(ContentR(related_id, kind));
    }

ContentR::ContentR(int next, int next_type)
{
    __next = next;
    __next_type = next_type;
}