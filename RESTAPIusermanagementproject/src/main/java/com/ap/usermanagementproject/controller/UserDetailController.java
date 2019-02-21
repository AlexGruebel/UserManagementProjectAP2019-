package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.UserDetail;
import com.ap.usermanagementproject.repositories.UserDetailRepository;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/userdetail")
public class UserDetailController extends BaseController<UserDetail, UserDetailRepository>{}