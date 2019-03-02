package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.PermissionEntity;
import com.ap.usermanagementproject.repositories.PermissionRepository;

import org.springframework.stereotype.Service;
@Service
public class PermissionCRUDService extends BaseCRUDService<PermissionEntity, PermissionRepository> {}