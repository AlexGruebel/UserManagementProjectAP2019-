package com.ap.usermanagementproject.services;

import com.ap.usermanagementproject.entities.GroupDetail;
import com.ap.usermanagementproject.repositories.GroupDetailRepository;
import org.springframework.stereotype.Service;

@Service
public class GroupDetailCRUDService extends BaseCRUDService<GroupDetail, GroupDetailRepository> {}