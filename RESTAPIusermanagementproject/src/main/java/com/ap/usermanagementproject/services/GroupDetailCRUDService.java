package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.GroupDetailEntity;
import com.ap.usermanagementproject.repositories.GroupDetailRepository;
import org.springframework.stereotype.Service;

@Service
public class GroupDetailCRUDService extends BaseCRUDService<GroupDetailEntity, GroupDetailRepository> {}