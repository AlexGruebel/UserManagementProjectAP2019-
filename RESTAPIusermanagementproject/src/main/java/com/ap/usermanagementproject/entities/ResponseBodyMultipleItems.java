package com.ap.usermanagementproject.entities;

import java.util.ArrayList;
import java.util.List;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.repository.JpaRepository;

public class ResponseBodyMultipleItems<T> {
    private int page;
    private short limit;
    private List<T> items;

    public ResponseBodyMultipleItems(int page, short limit, List<T> items){
        setPage(page);
        setLimit(limit);
        setItems(items);
    }

    /**
     * @param page the page to set
     */
    public void setPage(int page) {
        this.page = page;
    }

    /**
     * @return the page
     */
    public int getPage() {
        return page;
    }

    /**
     * @param limit the limit to set
     */
    public void setLimit(short limit) {
        this.limit = limit;
    }
    /**
     * @return the limit
     */
    public short getLimit() {
        return limit;
    }

    /**
     * @param items the items to set
     */
    public void setItems(List<T> items) {
        this.items = items;
    }

    /**
     * @return the items
     */
    public List<T> getItems() {
        return items;
    }

    public void fillBodyWithRepository(JpaRepository<T, Integer> repository){
        List<T> items = new ArrayList<T>();
        //all entities should have an id property, so the fixed text is in this context fine
        repository.findAll(PageRequest.of((page - 1) * limit, limit, Sort.by(Sort.Direction.ASC, "id")))
                                 .forEach(user -> items.add(user));
        setItems(items);
    }
}