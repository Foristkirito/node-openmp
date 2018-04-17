{
    "targets": [
        {
            "target_name": "node-openmp",
            "defines": [
                "VERSION=0.0.1",
                "NAPI_DISABLE_CPP_EXCEPTIONS"
            ],
            "sources": [
                "src/main.cc"
            ],
            "include_dirs": [
                "<!(echo %cd%/node_modules/node-addon-api)"               
            ],
            "conditions": [
                [
                    'OS=="win"',
                    {
                        'msvs_settings': {
                            'VCCLCompilerTool' : {
                                'AdditionalOptions' : ['/MT','/openmp']
                            }
                        }
                    }
                ]
            ]
        }
    ]
}