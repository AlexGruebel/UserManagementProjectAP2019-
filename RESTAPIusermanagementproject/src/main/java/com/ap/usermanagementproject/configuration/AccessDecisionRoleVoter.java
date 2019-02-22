package com.ap.usermanagementproject.configuration;

import java.util.Collection;

import com.ap.usermanagementproject.entities.UserPrincipal;
import com.ap.usermanagementproject.repositories.UserPermissionRepository;

import org.springframework.security.access.AccessDecisionVoter;
import org.springframework.security.access.ConfigAttribute;
import org.springframework.security.core.Authentication;
import org.springframework.security.web.FilterInvocation;

public class AccessDecisionRoleVoter implements AccessDecisionVoter<Object> {

    private UserPermissionRepository userPermissionRepository;

    public AccessDecisionRoleVoter(UserPermissionRepository userPermissionRepository){
        this.userPermissionRepository = userPermissionRepository;
    }

    @Override
    public int vote(Authentication authentication, Object object, Collection collection) {
        UserPrincipal prinzipal = ((UserPrincipal) authentication.getPrincipal());
        int userId = prinzipal.getId();

        FilterInvocation filterInvoation = (FilterInvocation) object;
        String url = filterInvoation.getRequestUrl();

        if(userPermissionRepository.existsByUserIdAndPermissionLike(userId, url)){
            return ACCESS_GRANTED;
        }else{
            return ACCESS_DENIED;
        }
    }

    @Override
    public boolean supports(Class clazz) {
        return true;
    }

    @Override
    public boolean supports(ConfigAttribute attribute) {
        return true;
    }
}