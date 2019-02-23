package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.ResponseBodyMultipleItems;
import com.ap.usermanagementproject.entities.IEntity;
import com.ap.usermanagementproject.services.BaseRService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.web.bind.annotation.*;

public abstract class BaseGetController<T extends IEntity
                                        , R extends JpaRepository<T, Integer>
                                        , S extends BaseRService<T, R>> 
{
    private S service;
    @Autowired
    private void setService(S service){
        this.service = service;
    }

    /**
     * @return the repository
     */
    public S getService() {
        return service;
    }

    @GetMapping
    public ResponseBodyMultipleItems<T> get(@RequestParam(required = false, defaultValue = "1") Integer page
                                                  ,@RequestParam(required = false, defaultValue = "100") Short limit) 
    {        
        ResponseBodyMultipleItems<T> body = new ResponseBodyMultipleItems<T>(
            page,
            limit,
            service.findAll(PageRequest.of((page - 1) * limit, limit, Sort.by(Sort.Direction.ASC, "id"))).getContent()
        );
        return body;
    }
}