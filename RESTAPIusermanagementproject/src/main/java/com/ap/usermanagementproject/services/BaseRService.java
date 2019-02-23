package com.ap.usermanagementproject.services;
import java.util.List;
import java.util.Optional;

import com.ap.usermanagementproject.entities.IEntity;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;

public abstract class BaseRService<T extends IEntity, R extends JpaRepository<T, Integer>> {
    private R repository;

    /**
     * @param jpaRepository the jpaRepository to set
     */
    @Autowired
    public void setRepository(R repository) {
        this.repository = repository;
    }

    protected R getRepository() {
        return this.repository;
    }

    public Page<T> findAll(Pageable pageable) {
        return this.repository.findAll(pageable);
    }

    public List<T> findAll() {
        return this.repository.findAll();
    }
}