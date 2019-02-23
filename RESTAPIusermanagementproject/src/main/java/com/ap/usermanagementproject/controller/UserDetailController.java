package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.UserDetail;
import com.ap.usermanagementproject.entities.UserDetailWithPWEntity;
import com.ap.usermanagementproject.repositories.UserDetailRepository;
import com.ap.usermanagementproject.services.UserDetailCRUDService;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/userdetail")
public class UserDetailController extends ExtBaseController<UserDetail
                                                        ,UserDetailWithPWEntity
                                                        ,UserDetailRepository
                                                        ,UserDetailCRUDService>{}