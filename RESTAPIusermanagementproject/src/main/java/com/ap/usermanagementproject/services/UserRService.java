package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.User;
import com.ap.usermanagementproject.repositories.UserRepository;
import org.springframework.stereotype.Service;
@Service
public class UserRService extends BaseRService<User, UserRepository> {}