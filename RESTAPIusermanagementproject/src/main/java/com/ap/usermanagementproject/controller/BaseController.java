package com.ap.usermanagementproject.controller;

import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;

public abstract class BaseController<T, R extends JpaRepository<T, Integer>> extends BaseGetController<T, R> {

    @GetMapping(value = "/{id}")
    public T get(@PathVariable int id) {
        Optional<T> findById = super.getRepository().findById(id);
        return (T) findById;
    }

    @PostMapping
    public T post(@RequestBody T entity) {
        super.getRepository().save(entity);
        return entity;
    }
    
    @PutMapping(value="/{id}")
    public T put(@PathVariable int id, @RequestBody T entity) {
        super.getRepository().save(entity);
        return entity;
    }

    @DeleteMapping(value="/{id}")
    public void delete(@PathVariable int id){
        super.getRepository().deleteById(id);
    }
} 