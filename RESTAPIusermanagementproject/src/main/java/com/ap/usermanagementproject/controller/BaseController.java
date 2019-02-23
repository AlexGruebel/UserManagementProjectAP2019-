package com.ap.usermanagementproject.controller;

import java.util.Optional;

import com.ap.usermanagementproject.entities.IEntity;
import com.ap.usermanagementproject.services.BaseCRUDService;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;

public abstract class BaseController<T extends IEntity
                                    ,R extends JpaRepository<T, Integer>
                                    ,S extends BaseCRUDService<T, R>> extends BaseGetController<T, R, S> 
{

    @GetMapping(value = "/{id}")
    public Optional<T> get(@PathVariable int id) {
        return super.getService().getEntityById(id);
    }

    @PostMapping
    public T post(@RequestBody T entity) {
        return super.getService().saveEntity(entity);
    }
    
    @PutMapping(value="/{id}")
    public T put(@PathVariable int id, @RequestBody T entity) throws Exception {
        return super.getService().updateEntity(entity, id);
    }

    @DeleteMapping(value="/{id}")
    public void delete(@PathVariable int id){
        super.getService().deleteEntityById(id);
    }
} 