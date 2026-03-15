#include "Page.h"

/*==============================================================PAGE_MANEGE==============================================================*/

PAGE_MANEGE::PAGE_MANEGE(void)
{
    _pageCount = 0;
}

bool PAGE_MANEGE::is_a_page(const std::string& page_name)
{
    if(_pages.find(page_name) != _pages.end())
        return true;
    return false;
}

bool PAGE_MANEGE::create_page(const std::string& page_name, page_callback static_callback, void* context_static, page_callback dynamic_callback, void* context_dynamic)
{
    if(is_a_page(page_name) == true)
        return false;

    PAGE* new_page = new PAGE();
    
    new_page->register_page(page_name, static_callback, context_static, dynamic_callback, context_dynamic);

    _pages[page_name] = new_page;

    _pageCount++;
    
    return true;
}

bool PAGE_MANEGE::delete_page(const std::string& page_name)
{
    if(is_a_page(page_name) == false)
        return false;

    PAGE* page = _pages[page_name];
    delete page;
    _pages.erase(page_name);

    _pageCount--;
    
    return true;
}

bool PAGE_MANEGE::change_page_static_callback(const std::string& page_name, page_callback static_callback)
{
    if(is_a_page(page_name) == false)
        return false;

    PAGE* page = _pages[page_name];
    page->_pageInfo.static_callback = static_callback;

    return true;
}

bool PAGE_MANEGE::change_page_static_context(const std::string& page_name, void* context_static)
{
    if(is_a_page(page_name) == false)
        return false;

    PAGE* page = _pages[page_name];  
    page->_pageInfo.context_static = context_static;

    return true;
}

bool PAGE_MANEGE::change_page_dynamic_callback(const std::string& page_name, page_callback dynamic_callback)
{
    if(is_a_page(page_name) == false)
        return false;

    PAGE* page = _pages[page_name];
    page->_pageInfo.dynamic_callback = dynamic_callback;

    return true;
}

bool PAGE_MANEGE::change_page_dynamic_context(const std::string& page_name, void* context_dynamic)
{
    if(is_a_page(page_name) == false)
        return false;

    PAGE* page = _pages[page_name];  
    page->_pageInfo.context_dynamic = context_dynamic;

    return true;
}

void PAGE_MANEGE::show_page(const std::string& page_name)
{
    if(is_a_page(page_name) == false)
        return;
    
    PAGE* page = _pages[page_name];  
    if(page->_pageInfo.page_name == _last_page_name)
        page->updata_dynamic();
    else 
    {
        page->updata();
        _last_page_name = page->_pageInfo.page_name;
    }
}

/*=================================================================PAGE=================================================================*/

PAGE::PAGE(void)
{
    _pageInfo.register_static_page = false;
    _pageInfo.static_callback = nullptr;
    _pageInfo.context_static = nullptr;
    _pageInfo.register_dynamic_page = false;
    _pageInfo.dynamic_callback = nullptr;
    _pageInfo.context_dynamic = nullptr;
}

void PAGE::register_page(const std::string& page_name, page_callback static_callback, void* context_static, page_callback dynamic_callback, void* context_dynamic)
{
    _pageInfo.page_name = page_name;
    
    if(static_callback != nullptr)
    {
        _pageInfo.register_static_page = true;
        _pageInfo.static_callback = static_callback;
        _pageInfo.context_static = context_static;
    }

    if(dynamic_callback != nullptr)
    {
        _pageInfo.register_dynamic_page = true;
        _pageInfo.dynamic_callback = dynamic_callback;
        _pageInfo.context_dynamic = context_dynamic;
    }
}

void PAGE::updata_static(void)
{
    if(_pageInfo.register_static_page == true)
        _pageInfo.static_callback(_pageInfo.context_static);
}

void PAGE::updata_dynamic(void)
{
    if(_pageInfo.register_dynamic_page == true)
        _pageInfo.dynamic_callback(_pageInfo.context_dynamic);
}

void PAGE::updata(void)
{
    if(_pageInfo.register_static_page == true)
        _pageInfo.static_callback(_pageInfo.context_static);

    if(_pageInfo.register_dynamic_page == true)
        _pageInfo.dynamic_callback(_pageInfo.context_dynamic);
}
