#ifndef __PAGE_H__
#define __PAGE_H__

#include <stdio.h>
#include <map>

class PAGE
{
    friend class PAGE_MANEGE;

    public:
        typedef void (*page_callback)(void* context);
            
        PAGE(void);

    protected:

        void register_page(const std::string& page_name, page_callback static_callback, void* context_static, page_callback dynamic_callback, void* context_dynamic);

        void updata(void);
        void updata_static(void);
        void updata_dynamic(void);

        typedef struct
        {
            std::string page_name;

            bool register_static_page;
            page_callback static_callback;
            void* context_static;

            bool register_dynamic_page;
            page_callback dynamic_callback;
            void* context_dynamic;

        }PageInfo;
        PageInfo _pageInfo;

    private:


};

class PAGE_MANEGE : public PAGE
{
    public:

        PAGE_MANEGE(void);

        void show_page(const std::string& page_name);

        bool create_page(const std::string& page_name, page_callback static_callback, void* context_static, page_callback dynamic_callback, void* context_dynamic);
        bool delete_page(const std::string& page_name);

        bool change_page_static_callback(const std::string& page_name, page_callback static_callback);
        bool change_page_static_context(const std::string& page_name, void* context_static);
        bool change_page_dynamic_callback(const std::string& page_name, page_callback dynamic_callback);
        bool change_page_dynamic_context(const std::string& page_name, void* dynamic_static);

        bool is_a_page(const std::string& page_name);

        inline uint16_t get_pageCount(void) { return _pageCount; }

    private:
        
        uint16_t _pageCount;

        std::string _last_page_name;

        std::map<std::string, PAGE*> _pages;
};



#endif
