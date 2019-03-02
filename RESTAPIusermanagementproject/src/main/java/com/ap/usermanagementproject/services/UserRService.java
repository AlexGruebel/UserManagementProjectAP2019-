package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.UserEntity;
import com.ap.usermanagementproject.repositories.UserRepository;
import org.springframework.stereotype.Service;
@Service
public class UserRService extends BaseRService<UserEntity, UserRepository> {}