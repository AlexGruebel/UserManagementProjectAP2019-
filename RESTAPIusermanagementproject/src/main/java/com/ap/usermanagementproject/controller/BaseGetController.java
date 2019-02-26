package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.ResponseBodyMultipleItems;
import com.ap.usermanagementproject.entities.IEntity;

import java.util.Collection;

import javax.servlet.http.HttpServletRequest;
import com.ap.usermanagementproject.services.BaseRService;
import com.ap.usermanagementproject.util.CheckPermissionUtil;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.http.HttpRequest;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
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
                                                  ,@RequestParam(required = false, defaultValue = "100") Short limit, Authentication auth, HttpServletRequest request) 
    {        
        CheckPermissionUtil.checkPermission(request.getRequestURI(), ((Collection<GrantedAuthority>) auth.getAuthorities()));        
        ResponseBodyMultipleItems<T> body = new ResponseBodyMultipleItems<T>(
            page,
            limit,
            service.findAll(PageRequest.of((page - 1) * limit, limit, Sort.by(Sort.Direction.ASC, "id"))).getContent()
        );
        return body;
    }
}