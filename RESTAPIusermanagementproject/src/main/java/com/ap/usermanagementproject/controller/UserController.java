package com.ap.usermanagementproject.controller;

import com.ap.usermanagementproject.entities.User;
import com.ap.usermanagementproject.repositories.UserRepository;
import com.ap.usermanagementproject.services.UserRService;

import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/user")
public class UserController extends BaseGetController<User, UserRepository, UserRService>{}