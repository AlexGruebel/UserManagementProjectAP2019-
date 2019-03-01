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

    @Autowired
    public void setRepository(R repository) {
        this.repository = repository;
    }

    protected R getRepository() {
        return this.repository;
    }

    /**
     * returns an specific range of Entites
     * @param Pageable to specify the range of entities to return for example the first 100 Entities in the DB
     * @return Page
     */
    public Page<T> findAll(Pageable pageable) {
        return getRepository().findAll(pageable);
    }

    public List<T> findAll() {
        return getRepository().findAll();
    }
}