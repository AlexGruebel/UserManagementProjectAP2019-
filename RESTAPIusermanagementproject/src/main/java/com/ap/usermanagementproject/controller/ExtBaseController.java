package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.IEntity;
import com.ap.usermanagementproject.services.BaseCRUDService;

import org.springframework.data.jpa.repository.JpaRepository;

public abstract class ExtBaseController<RT extends IEntity
                                    ,T extends RT
                                    ,R extends JpaRepository<RT, Integer>
                                    ,S extends BaseCRUDService<RT, R>> extends BaseController<RT, R, S>
{}