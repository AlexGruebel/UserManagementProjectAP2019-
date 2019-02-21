package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.ResponseBodyMultipleItems;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.web.bind.annotation.*;

public abstract class BaseGetController<T, R extends JpaRepository<T, Integer>> {

    private R repository;

    @Autowired
    private void setRepository(R repository){
        this.repository = repository;
    }

    /**
     * @return the repository
     */
    public R getRepository() {
        return repository;
    }

    @GetMapping
    public ResponseBodyMultipleItems<T> get(@RequestParam(required = false, defaultValue = "1") Integer page
                                                  ,@RequestParam(required = false, defaultValue = "100") Short limit) 
    {        
        ResponseBodyMultipleItems<T> body = new ResponseBodyMultipleItems<T>(page, limit);
        body.fillBodyWithRepository(getRepository());
        return body;
    }
}