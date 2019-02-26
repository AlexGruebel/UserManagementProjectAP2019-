package com.ap.usermanagementproject.controller;

import java.nio.file.AccessDeniedException;
import java.util.Collection;
import java.util.Optional;
import java.util.Set;

import javax.servlet.http.HttpServletRequest;

import com.ap.usermanagementproject.entities.IEntity;
import com.ap.usermanagementproject.entities.UserAuthorityEntity;
import com.ap.usermanagementproject.services.BaseCRUDService;
import com.ap.usermanagementproject.util.CheckPermissionUtil;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.http.HttpRequest;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.GrantedAuthority;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

public abstract class BaseController<T extends IEntity, R extends JpaRepository<T, Integer>, S extends BaseCRUDService<T, R>>
        extends BaseGetController<T, R, S> {
    private String requestMapping;

    public BaseController() {
        requestMapping = this.getClass().getAnnotation(RequestMapping.class).value()[0];
    }

    @GetMapping(value = "/{id}")
    public Optional<T> get(@PathVariable int id, Authentication auth, HttpServletRequest request)
            throws AccessDeniedException {
        CheckPermissionUtil.checkPermission(request.getRequestURI(), ((Collection<GrantedAuthority>) auth.getAuthorities()));
        return super.getService().getEntityById(id);
    }

    @PostMapping
    public T post(@RequestBody T entity, Authentication auth, HttpServletRequest request) {
        CheckPermissionUtil.checkPermission(request.getRequestURI(), ((Collection<GrantedAuthority>) auth.getAuthorities()));
        return super.getService().saveEntity(entity);
    }
    
    @PutMapping(value="/{id}")
    public T put(@PathVariable int id, @RequestBody T entity, Authentication auth, HttpServletRequest request) throws Exception {
        CheckPermissionUtil.checkPermission(request.getRequestURI(), ((Collection<GrantedAuthority>) auth.getAuthorities()));
        return super.getService().updateEntity(entity, id);
    }

    @DeleteMapping(value="/{id}")
    public void delete(@PathVariable int id, Authentication auth, HttpServletRequest request){
        CheckPermissionUtil.checkPermission(request.getRequestURI(), ((Collection<GrantedAuthority>) auth.getAuthorities()));
        super.getService().deleteEntityById(id);
    }

} 