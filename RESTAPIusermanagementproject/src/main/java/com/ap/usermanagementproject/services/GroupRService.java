package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.Group;
import com.ap.usermanagementproject.repositories.GroupRepository;
import org.springframework.stereotype.Service;
@Service
public class GroupRService extends BaseRService<Group, GroupRepository> {}